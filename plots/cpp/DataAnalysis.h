#include <iostream>
#include <algorithm>
#include <random>
#include <istream>
#include <unordered_set>
#include <string>
#include <unordered_map>
#include <sstream>
#include <vector>
#include "RandomVariates.h"
#include "Bootstrap.h"
#include "EmpiricalDistribution.h"
#include "BarGraph.h"
#include "Entropy.h"
#include "StatTools.h"
#include "DiscreteDistribution.h"
#include "Histogram.h"
#include "Bootstrap.h"
namespace dd = alex::statistics::distributions::discrete_distribution;

struct PStarRecord
{
    static struct Element
    {
        std::string industry, corp;
        size_t corpSize, nStar, successes;
        double pStar, pStarPrime, maxP;
        bool converged;
    };

    std::vector<Element> sample;
    std::map<std::string, double> stats;
};

void generate_N_star(std::istream& is, std::ostream& os, const std::vector<double>& pStars, size_t start = 0, size_t end = std::numeric_limits<size_t>::max());
std::unordered_map<double, PStarRecord> generate_N_star_stage_2(std::istream& is);
void generate_n_star_analysis_2(std::unordered_map<double, PStarRecord>& pstars);
void generate_n_star_analysis_1(std::unordered_map<double, PStarRecord>& pstars);
void generate_n_star_analysis_7(std::unordered_map<double, PStarRecord>& pstars, std::ofstream& os);

void outputVariance(std::istream& is, std::ostream& os)
{
    std::string s;
    double pStar;
    double nStar;
    std::map<double, std::vector<double>> mp;

    while (is)
    {
        is >> s; //std::cout << s << std::endl;
        is >> s; //std::cout << s << std::endl;
        is >> s; //std::cout << s << std::endl;
        is >> s; //std::cout << s << std::endl;
        is >> s; //std::cout << s << std::endl;
        is >> s; //std::cout << s << std::endl;
        is >> pStar;
        is >> nStar;
        is >> s; //std::cout << s << std::endl;
        is >> s; //std::cout << s << std::endl;
        is >> s; //std::cout << s << std::endl;
        //std::cout << pStar << "\t" << nStar << std::endl;
        mp[pStar].push_back(nStar);
        //system("pause");
    }

    for (auto x : mp)
    {
        pStar = x.first;
        auto samp = x.second;

        std::cout << "pStar: " << pStar << std::endl;
        std::cout << "sampe size: " << samp.size() << std::endl;
        

        auto sampMean = alex::statistics::mean(samp);
        auto sampVar = alex::statistics::sampleVariance(samp);
        std::cout << "sample variance: " << sampVar << std::endl;

        auto t = alex::statistics::invStudentTCdf(samp.size() - 1, 0.975);
        std::cout << "t: " << t << std::endl;

        auto lower = sampMean - t * std::sqrt(sampVar / samp.size());
        auto upper = sampMean + t * std::sqrt(sampVar / samp.size());
        os << pStar << "\t" << sampMean << "\t" << lower << "\t" << upper << std::endl;
    }
};

// generate n star analysis versus p_star
// so, for a given p_star, calculate n_star variance (ignore groups for now),
// n_star mean, etc.
std::unordered_map<double, PStarRecord> generate_N_star_stage_2(std::istream& is)
{
    // exp_no   line_no converged   industry    corp    corp_size   p_star  n_star  p_star_*    successes   max_p

    size_t expNo, lineNo, corpSize, nStar, successes;
    std::string industry, corp;
    double pStar, pStarPrime, maxP;
    bool converged;
    std::unordered_map<double, PStarRecord> pStarRecords;

    while (is)
    {
        std::stringstream ss;
        double maxP;
        std::string line;
        std::getline(is, line);

        ss << line;
        ss >> expNo >> lineNo >> converged >> industry >> corp >> corpSize >> pStar >> nStar >> pStarPrime >> successes >> maxP;
        pStarRecords[pStar].sample.push_back(PStarRecord::Element { industry, corp, corpSize, nStar, successes, pStar, pStarPrime, maxP, converged });
    }

    return pStarRecords;
}

void generate_n_star_analysis_8(std::unordered_map<double, PStarRecord>& pstars)
{
    for (auto& x : pstars)
    {
        size_t convergedCount = 0;
        const auto pstar = x.first;
        const auto& rec = x.second;

        if (pstar != 0.3)
            continue;
        
        std::vector<double> nstars;
        for (const auto& y : rec.sample)
        {
            if (y.converged)
            {
                ++convergedCount;
                nstars.push_back(y.nStar);
            }
        }

        auto pop = std::ifstream("pop_data");
        alex::statistics::BarGraph bg;
        std::vector<int> samps;
        int x;
        while (pop >> x)
            samps.push_back(x);
        bg.construct(samps);
        bg.outputRaw("pop_data_pdf");

        alex::statistics::Entropy<> ent;
        alex::statistics::estimation::Bootstrap<> bs(ent);
        size_t xlow = std::numeric_limits<size_t>::max();
        size_t xhigh = std::numeric_limits<size_t>::min();

        xlow = 5000;
        xhigh = 11000;

        for (size_t n = 50; n <= 1000; n += 25)
        {
            std::ofstream os("epdf.gp");
            std::string base;
            base += "set title \"5th Percentile Sampling Distribution (Empirical CDF's Sample Size = " + std::to_string(n) + ")\"\n";
            base += "set xlabel \"5th Percentile (0.05 Quantile)\"\n";
            base += "set ylabel \"Cumulative Probability\"\n";
            base += "set key left top\n";
            base += "set grid x\n";
            base += "set xrange [" + std::to_string(xlow) + ":" + std::to_string(xhigh) + "]\n";
            base += "set yrange [0:1]\n";

            base += "plot \"pop_data_pdf\" using 1:3 title \"Population\", \\\n";
            base +=      "\"sample_data_pdf\" using 1:3 title \"Empirical\"\n";
            base += "call \"gif_export.plt\" \"epdf_" + std::to_string(n) + ".gif\"";
            os << base; os.close();

            auto samps2 = bs.getQuantileSamples2(nstars, n, 0.05, 10000, 0);
            std::vector<int> s2; s2.reserve(samps2.size());
            for (auto x : samps2)
                s2.push_back(x);

            bg.construct(s2);
            bg.outputRaw("sample_data_pdf");
            std::system("c:\\gnuplot\\bin\\gnuplot epdf.gp");
        }
    }
}

// generate sampling distribution using bootstrap resampling
void generate_n_star_analysis_7(std::unordered_map<double, PStarRecord>& pstars, std::ofstream& os)
{
    for (auto& x : pstars)
    {
        size_t convergedCount = 0;
        const auto pstar = x.first;
        const auto& rec = x.second;

        std::vector<double> nstars;
        for (const auto& y : rec.sample)
        {
            if (y.converged)
            {
                ++convergedCount;
                nstars.push_back(y.nStar);
            }
        }

        alex::statistics::Entropy<> ent;
        alex::statistics::estimation::Bootstrap<> bs(ent);

        auto samp = bs.getQuantileSamples(nstars, 0.05, 10000, 0);
        for (auto x : samp)
            os << x << std::endl;
    }
}


// experiments with using bs to estimate median, then bs to estimate variance of median,
// then see if its consistent with just booststrap of median and throwing out 2.5% from both ends
void generate_n_star_analysis_6(std::unordered_map<double, PStarRecord>& pstars, std::ofstream& os)
{
    for (auto& x : pstars)
    {
        size_t convergedCount = 0;
        const auto pstar = x.first;
        const auto& rec = x.second;

        std::vector<double> nstars;
        for (const auto& y : rec.sample)
        {
            if (y.converged)
            {
                ++convergedCount;
                nstars.push_back(y.nStar);
            }
        }

        alex::statistics::Entropy<> ent;
        alex::statistics::estimation::Bootstrap<> bs(ent);

        double alpha = 0.05;

        for (double p = 0.0; p < 0.05; p += 0.01)
        {
            auto samp = bs.getQuantileSamples(nstars, p, 50000, 0);
            auto pr = bs.getQuantile(nstars, p, 50000, alpha);
            auto median = alex::statistics::mean(samp);
            //auto var = alex::statistics::sampleVariance(samp);
            //auto k = alex::statistics::invStudentTCdf(samp.size() - 1, p);
            //auto lower = median - k * std::sqrt(var);
            //auto upper = median + k * std::sqrt(var);
            os << pstar << "\t" << p << "\t" << median << "\t" << pr.first << "\t" << pr.second << std::endl;
        }

        for (double p = 0.05; p < 0.5; p += 0.2)
        {
            auto samp = bs.getQuantileSamples(nstars, p, 50000, 0);
            auto pr = bs.getQuantile(nstars, p, 50000, alpha);
            auto median = alex::statistics::mean(samp);
            //auto var = alex::statistics::sampleVariance(samp);
            //auto k = alex::statistics::invStudentTCdf(samp.size() - 1, p);
            //auto lower = median - k * std::sqrt(var);
            //auto upper = median + k * std::sqrt(var);
            os << pstar << "\t" << p << "\t" << median << "\t" << pr.first << "\t" << pr.second << std::endl;
        }

        auto samp = bs.getQuantileSamples(nstars, 0.5, 50000, 0);
        auto pr = bs.getQuantile(nstars, 0.5, 50000, alpha);
        auto median = alex::statistics::mean(samp);
        //auto var = alex::statistics::sampleVariance(samp);
        //auto k = alex::statistics::invStudentTCdf(samp.size() - 1, p);
        //auto lower = median - k * std::sqrt(var);
        //auto upper = median + k * std::sqrt(var);
        os << pstar << "\t" << 0.5 << "\t" << median << "\t" << pr.first << "\t" << pr.second << std::endl;


        os << std::endl << std::endl;
    }
}

// experiments with using bs to estimate median, then bs to estimate variance of median,
// then see if its consistent with just booststrap of median and throwing out 2.5% from both ends
void generate_n_star_analysis_5(std::unordered_map<double, PStarRecord>& pstars)
{
    for (auto& x : pstars)
    {
        size_t convergedCount = 0;
        const auto pstar = x.first;
        const auto& rec = x.second;
        
        std::vector<double> nstars;
        for (const auto& y : rec.sample)
        {
            if (y.converged)
            {
                ++convergedCount;
                nstars.push_back(y.nStar);
            }
        }

        alex::statistics::Entropy<> ent;
        alex::statistics::estimation::Bootstrap<> bs(ent);
        auto rv = alex::statistics::random_variates::normal<double>(100, 5, ent);
        nstars.clear();
        for (int i = 0; i < 10000; ++i)
            nstars.push_back(rv());

        auto median1 = bs.estimate(nstars, alex::statistics::Statistic::Median, 5000, 0.05);
        auto samp2 = bs.getSample(nstars, alex::statistics::Statistic::Median, 5000, 0);
        auto median2 = alex::statistics::mean(samp2);
        auto var2 = alex::statistics::sampleVariance(samp2);
        auto k = alex::statistics::invStudentTCdf(samp2.size() - 1, 0.975);
        auto median2_lower = median2 - k * std::sqrt(var2);
        auto median2_upper = median2 + k * std::sqrt(var2);

        auto mean1 = bs.estimate(nstars, alex::statistics::Statistic::Mean, 5000, 0.05);
        auto mu_samp2 = bs.getSample(nstars, alex::statistics::Statistic::Mean, 5000, 0);
        auto mean2 = alex::statistics::mean(mu_samp2);
        auto mu_var2 = alex::statistics::sampleVariance(mu_samp2);
        auto mean2_lower = mean2 - k * std::sqrt(mu_var2);
        auto mean2_upper = mean2 + k * std::sqrt(mu_var2);
        auto mean3 = alex::statistics::mean(nstars);
        auto mu_var3 = alex::statistics::sampleVariance(nstars);
        auto mean3_lower = mean3 - k * std::sqrt(mu_var3 / nstars.size());
        auto mean3_upper = mean3 + k * std::sqrt(mu_var3 / nstars.size());

        std::system("cls");
        std::cout << "mean [" << mean3_lower << ", " << mean3_upper << "]" << std::endl;
        std::cout << "mean centered [" << mean1.first << ", " << mean1.second << "]" << std::endl;
        std::cout << "mean t-stat [" << mean2_lower << ", " << mean2_upper << "]" << std::endl;
        std::cout << "median centered [" << median1.first << ", " << median1.second << "]" << std::endl;
        std::cout << "median t-stat [" << median2_lower << ", " << median2_upper << "]" << std::endl;
        std::system("pause");
    }
}

void generate_n_star_analysis_4(std::unordered_map<double, PStarRecord>& pstars)
{
    for (auto& x : pstars)
    {
        size_t convergedCount = 0;
        const auto pstar = x.first;
        const auto& rec = x.second;
        
        std::vector<double> nstars;
        for (const auto& y : rec.sample)
        {
            if (y.converged)
            {
                ++convergedCount;
                nstars.push_back(y.nStar);
            }
        }

        alex::statistics::Histogram<> histo;
        double mu = alex::statistics::mean(nstars);
        double var = alex::statistics::sampleVariance(nstars);
        // large population -- N -> infinity, fpc = 1
        auto mu_b = alex::statistics::invStudentTCdf(nstars.size() - 1, 0.975) * var / nstars.size();       

        double p = 0;
        for (size_t i = 0; i < histo.size(); ++i)
        {
            auto& bin = histo.get(0);
            bin.freq;
        }


        std::map<std::string, std::string> opts = {{"title", "p* = " + std::to_string(pstar) + ", mu = " + std::to_string(mu) + ", sd = " + std::to_string(std::sqrt(var))}};
        std::stringstream ss;
        ss << "pstar=" << pstar << "_vs_nstar_95_percent.gif";


        histo.construct(nstars, 30);        
        histo.outputGIF_4(ss.str(), opts);
    }
}


// p* vs mean{n*} histogram (bootstrap)
void generate_n_star_analysis_3(std::unordered_map<double, PStarRecord>& pstars)
{
    for (auto& x : pstars)
    {
        size_t convergedCount = 0;
        const auto pstar = x.first;
        const auto& rec = x.second;
        
        std::vector<double> nstars;
        for (const auto& y : rec.sample)
        {
            if (y.converged)
            {
                ++convergedCount;
                nstars.push_back(y.nStar);
            }
        }

        alex::statistics::Entropy<> ent;
        alex::statistics::estimation::Bootstrap<> bs(ent);
        auto mu_bs = bs.estimate(nstars, alex::statistics::Statistic::Mean, 5000, 0.05);
        alex::statistics::Histogram<> histo;

        auto mu_bs_samp = bs.getSample(nstars, alex::statistics::Statistic::Mean, 5000, 0.05);
        histo.construct(mu_bs_samp, 30);

        std::map<std::string, std::string> opts = {{"title", "p* = " + std::to_string(pstar) + ", [" + std::to_string(mu_bs.first) + ", " + std::to_string(mu_bs.second) + "]"}};
        std::stringstream ss;
        ss << "pstar_" << pstar << "_vs_mean_nstar_bs_2.gif";       
        histo.outputGIF_3(ss.str(), opts);
    }
}


// p* vs mean{n*} histogram (bootstrap) ???
void generate_n_star_analysis_2(std::unordered_map<double, PStarRecord>& pstars)
{
    for (auto& x : pstars)
    {
        size_t convergedCount = 0;
        const auto pstar = x.first;
        const auto& rec = x.second;
        
        std::vector<double> nstars;
        for (const auto& y : rec.sample)
        {
            if (y.converged)
            {
                ++convergedCount;
                nstars.push_back(y.nStar);
            }
        }

        alex::statistics::Entropy<> ent;
        alex::statistics::estimation::Bootstrap<> bs(ent);
        auto mu_bs = bs.estimate(nstars, alex::statistics::Statistic::Mean, 5000, 0.05);
        alex::statistics::Histogram<> histo;

        auto mu_bs_samp = bs.getSample(nstars, alex::statistics::Statistic::Mean, 5000, 0.05);
        histo.construct(mu_bs_samp, 30);

        std::map<std::string, std::string> opts = {{"title", "p* = " + std::to_string(pstar) + ", [" + std::to_string(mu_bs.first) + ", " + std::to_string(mu_bs.second) + "]"}};
        opts["xmin"] = "1e2";
        opts["xmax"] = "1e7";
        opts["ymin"] = "0";
        opts["ymax"] = "50";

        std::stringstream ss;
        ss << "pstar_" << pstar << "_vs_mean_nstar_bs.gif";
        
        histo.outputGIF_1(ss.str(), opts);
    }
}

void generate_n_star_analysis_1(std::unordered_map<double, PStarRecord>& pstars)
{
    for (auto& x : pstars)
    {
        size_t convergedCount = 0;
        const auto pstar = x.first;
        const auto& rec = x.second;
        
        std::vector<double> nstars;
        for (const auto& y : rec.sample)
        {
            if (y.converged)
            {
                ++convergedCount;
                nstars.push_back(y.nStar);
            }
        }

        alex::statistics::Entropy<> ent;
        alex::statistics::estimation::Bootstrap<> bs(ent);

        auto mu_bs = bs.estimate(nstars, alex::statistics::Statistic::Mean, 5000, 0.05);
        auto mu_bs_b = (mu_bs.second - mu_bs.first) / 2;
        auto mu_bs_mid = (mu_bs.first + mu_bs.second) / 2;

        auto sd_bs = bs.estimate(nstars, alex::statistics::Statistic::Deviation, 5000, 0.05);
        auto sd_bs_b = (sd_bs.second - sd_bs.first) / 2;
        auto sd_bs_mid = (sd_bs.first + sd_bs.second) / 2;

        auto skew_bs = bs.estimate(nstars, alex::statistics::Statistic::Skewness, 5000, 0.05);
        auto skew_bs_b = (skew_bs.second - skew_bs.first) / 2;
        auto skew_bs_mid = (skew_bs.first + skew_bs.second) / 2;

        auto kurt_bs = bs.estimate(nstars, alex::statistics::Statistic::Kurtosis, 5000, 0.05);
        auto kurt_bs_b = (kurt_bs.second - kurt_bs.first) / 2;
        auto kurt_bs_mid = (kurt_bs.first + kurt_bs.second) / 2;

        auto mu = alex::statistics::mean(nstars);
        auto var = alex::statistics::sampleVariance(nstars);
        auto kurt = alex::statistics::sampleKurtosis(nstars);
        auto skew = alex::statistics::sampleSkewness(nstars);
        auto mu_b = alex::statistics::invStudentTCdf(nstars.size() - 1, 0.975) * std::sqrt(var / nstars.size());

        std::stringstream ss;
        ss  << "mu = " << mu << " +- " << mu_b << ", "
            << "mu (bs) = " << mu_bs_mid << " +- " << mu_bs_b << ", "
            << "sd (bs) = " << sd_bs_mid << " +- " << sd_bs_b << ", "
            << "kurt (bs) = " << kurt_bs_mid << " +- " << kurt_bs_b << ", "
            << "skew (bs) = " << skew_bs_mid << " +- " << skew_bs_b;

        auto f = alex::statistics::Histogram<>();
        f.construct(nstars, 0.0, nstars.back(), 50);
        std::string fname = std::to_string(x.first);

        auto opts = std::map<std::string, std::string> {{"title", "p* = " + std::to_string(pstar) + ", mu = " + std::to_string(mu_bs_mid) + " +- " + std::to_string(mu_bs_b)}};
        opts["xmin"] = "1e2";
        opts["xmax"] = "1e7";
        opts["ymin"] = "0";
        opts["ymax"] = "50";

        f.outputGIF_1(fname + ".gif", opts);
    }
}


void generate_N_star(std::istream& is, std::ostream& os, const std::vector<double>& pStars, size_t start, size_t end)
{
    const size_t MAX_SUCCESSES = 5000;
    size_t corpSize, lineCount = 0, i = 0;
    std::string industry, corp;
    std::vector<size_t> ns;

    std::string line;
    size_t j = 0;
    while (is && j < start)
    {
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        ++j;
        std::cout << "\t* skipping line " << j << std::endl;
    }

    while (is && lineCount < end)
    {
        std::string line;
        std::getline(is, line);

        for (const auto pStar : pStars)
        {
            std::stringstream ss;
            double maxP;
            ss << line;
            ss >> industry >> corp >> corpSize >> maxP;

            if (maxP < pStar)
            {
                std::cout << "\t* skipping " << pStar << " on " << lineCount << std::endl;
                continue;
            }

            bool above = false;
            double p, pStarPrime = 0;
            size_t nStar = 0, n;
            size_t successes = 0;

            while (ss)
            {
                ss >> p >> n;
                if (above && successes >= MAX_SUCCESSES)
                    break;
                else if (p >= pStar)
                {
                    ++successes;
                    if (!above)
                    {
                        above = true;
                        nStar = n;
                        pStarPrime = p;
                    }
                }
                else if (above)
                    above = false;
            }

            if (above)
            {
                std::cout << "\t*[admitted: " << lineCount << "] "
                    << industry << "::" << corp << "::" << corpSize << "\t"
                    << pStar << " => " << nStar << " {"
                    << pStarPrime << "}" << std::endl;
            }
            else
            {
                std::cout << "\t*[not admitted: " << lineCount << "] "
                    << industry << "::" << corp << "::" << corpSize << "\t"
                    << pStar << " => " << nStar << " {"
                    << pStarPrime << "}" << std::endl;
            }

            os << i++ << "\t" << lineCount << "\t" << above << "\t"
                << industry << "\t" << corp << "\t" << corpSize << "\t"
                << pStar << "\t" << nStar << "\t" << pStarPrime << "\t"
                << successes << "\t" << maxP << std::endl;
        }
        ++lineCount;
    }
}