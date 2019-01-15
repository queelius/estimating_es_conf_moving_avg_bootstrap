#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>
#include <map>
#include "Bootstrap.h"

const double P_STAR = 0.3;
const double QUANTILE = 0.05;
const double CI_ALPHA = 0.05;
const size_t EMPIRICAL_CDF_SIZE = 450;
const size_t SAMPLE_SIZE = EMPIRICAL_CDF_SIZE;

std::vector<std::pair<double, double>> makeCdf(std::vector<double> vals)
{
    std::map<double, double> freq;

    double total = 0;
    for (auto v : vals)
    {
        ++total;
        if (freq.count(v) == 0)
        {
            freq[v] = 1;
        }
        else
        {
            ++freq[v];
        }
    }

    double acc = 0;
    for (auto& f : freq)
    {
        acc += f.second;
        f.second = acc;       
    }

    std::vector<std::pair<double, double>> cdf;
    for (const auto& f : freq)
    {
        cdf.push_back(std::make_pair(f.first, f.second / (double)total));
    }

    std::sort(cdf.begin(), cdf.end(), [](const std::pair<double, double>& p1, const std::pair<double, double>& p2) { return p1.first < p2.first; });
    return cdf;
};

std::vector<std::pair<double, double>> makePdf(std::vector<double> vals, double binWidth)
{
    std::vector<std::pair<double, double>> bins;
    std::sort(vals.begin(), vals.end());
    bins.push_back(std::make_pair(vals.front() + binWidth, 0));

    for (size_t i = 0; i < vals.size(); )
    {
        if (vals[i] < bins.back().first)
        {
            ++bins.back().second;
            ++i;
        }
        else
        {
            bins.push_back(std::make_pair(bins.back().first + binWidth, 0));
        }
    }

    for (auto& b : bins)
    {
        b.second /= vals.size();
    }

    return bins;
};

std::vector<double> makeSamplingDistribution(const std::string& filename, size_t sampleSize)
{
    auto infile = std::ifstream(filename.c_str());

    std::vector<double> vals;
    double val;
    while (infile >> val)
        vals.push_back(val);

    alex::statistics::estimation::Bootstrap<> bs;
    return bs.estimateSamplingDistribution(
        vals,
        [](const std::vector<double>& vs) { return alex::statistics::estimation::quantile(vs, QUANTILE); },
        sampleSize,
        sampleSize);
};

std::vector<double> makeSamplingDistribution(const std::vector<double>& vals, size_t sampleSize)
{
    alex::statistics::estimation::Bootstrap<> bs;
    return bs.estimateSamplingDistribution(
        vals,
        [](const std::vector<double>& vs) { return alex::statistics::estimation::quantile(vs, QUANTILE); },
        sampleSize,
        sampleSize);
};

void main()
{
    auto infile = std::ifstream("data_grouped_by_pstar");
    std::string tmp;
    double p;
    double n;
    std::vector<double> pop;
    while (infile)
    {
        infile >> tmp >> tmp >> tmp >> tmp >> tmp >> tmp >> p >> n >> tmp >> tmp >> tmp;
        if (p == P_STAR)
        {
            pop.push_back(n);
        }
    }

    if (pop.size() < EMPIRICAL_CDF_SIZE)
    {
        std::cout << "error: EMPIRICAL_CDF_SIZE > population" << std::endl;
        return;
    }
    infile.close();

    std::vector<double> empirical; empirical.reserve(EMPIRICAL_CDF_SIZE);
    std::random_shuffle(pop.begin(), pop.end());
    for (size_t i = 0; i < EMPIRICAL_CDF_SIZE; ++i)
    {
        empirical.push_back(pop[i]);
    }
    
    auto popSample = makeSamplingDistribution(pop, SAMPLE_SIZE);
    auto empiricalSample = makeSamplingDistribution(empirical, SAMPLE_SIZE);

    auto q = alex::statistics::estimation::quantile(pop, QUANTILE);
    std::cout << "population quantile(" << QUANTILE << "): " << q << std::endl;

    alex::statistics::estimation::Bootstrap<> bs;
    auto ciPop = bs.estimate(pop,
        [](const std::vector<double>& vs) { return alex::statistics::estimation::quantile(vs, QUANTILE); },
        SAMPLE_SIZE,
        SAMPLE_SIZE, CI_ALPHA);

    auto ciEmp = bs.estimate(empirical,
        [](const std::vector<double>& vs) { return alex::statistics::estimation::quantile(vs, QUANTILE); },
        SAMPLE_SIZE,
        SAMPLE_SIZE, CI_ALPHA);

    std::cout << "(1-" << CI_ALPHA << ")*100% two-sided CI (sampled population w/sample size " << SAMPLE_SIZE << "): [" << ciPop.first << ", " << ciPop.second << "]" << std::endl;
    std::cout << "w/point estimation " << alex::statistics::estimation::quantile(pop, QUANTILE) << std::endl;

    std::cout << "(1-" << CI_ALPHA << ")*100% two-sided CI (sampled empirical sample w/sample size " << SAMPLE_SIZE << "): [" << ciEmp.first << ", " << ciEmp.second << "]" << std::endl;
    std::cout << "w/point estimation " << alex::statistics::estimation::quantile(empirical, QUANTILE) << std::endl;

    auto popSamplingCdf = makeCdf(popSample);
    auto empSamplingCdf = makeCdf(empiricalSample);

    for (auto x : empSamplingCdf)
        std::cout << x.first << " => " << x.second << std::endl;

    auto popOut = std::ofstream("pcdf.data");
    for (auto x : popSamplingCdf)
    {
        popOut << x.first << "\t" << x.second << std::endl;
    }

    auto empOut = std::ofstream("ecdf.data");
    for (auto x : empSamplingCdf)
    {
        empOut << x.first << "\t" << x.second << std::endl;
    }
}