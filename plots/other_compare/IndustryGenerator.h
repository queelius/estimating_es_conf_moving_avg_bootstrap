#include <vector>
#include <string>
#include <iostream>
#include "DiscreteDistribution.h"
#include "DataGenerator.h"

struct Corporation
{
    std::string name;
    size_t size;
    dd::DiscreteDistribution<> corpFreqs;

    void simulate(size_t n, double p, const std::string& industry, std::ostream& out)
    {
        for (size_t i = 0; i < n; ++i)
        {
            out << industry << "\t" << name << "\t" << size << "\t" << p;
            auto vs = simulate_adversary(corpFreqs.size(), 12 * corpFreqs.size(), 50, 100000000, 50, p);
            for (const auto& v : vs)
            {
                out << "\t" << v.first << "\t" << v.second;
            }
            out << std::endl;
        }
    }
};

struct Industry
{
    void addCorp(size_t size, const std::string& name)
    {
        std::vector<int> sample;
        for (size_t i = 0; i < industryFreq.size() * (size_t)std::sqrt(size); ++i)
            sample.push_back(industryFreq.inverseCdf(entropy.get0_1()));

        Corporation corp;
        corp.name = name;
        corp.size = size;
        corp.corpFreqs = dd::fromFrequency(sample.begin(), sample.end());

        corps.push_back(corp);
    };

    void addIndustry(size_t vocabSize, double chisqr, const std::string& name)
    {
        industryFreq = alex::statistics::distributions::discrete_distribution::zipf(vocabSize);
        if (chisqr > 0)
        {

        }

        this->name = name;
    };

    void simulate(size_t n, double p, const std::string& filename)
    {
        std::ofstream out(filename, std::ios::app);
        for (auto corp : corps)
        {
            corp.simulate(n, p, name, out);
        }
        out.close();
    };

    size_t totalSize() const
    {
        size_t total = 0;
        for (auto corp : corps)
            total += corp.size;
        return total;
    };

    dd::DiscreteDistribution<> industryFreq;
    std::string name;
    std::vector<Corporation> corps;
    double varFactor;
};

void makeIndustries(const std::string& filename)
{
    Industry gov;
    gov.addIndustry(14000, "gov");
    gov.addCorp(12000, "NSA");
    gov.addCorp(13000, "IRS");
    gov.addCorp(10000, "DARPA");
    gov.addCorp(9000, "NASA");

    Industry health;
    health.addIndustry(7000, "health");
    health.addCorp(6000, "health-1");
    health.addCorp(8000, "health-2");
    health.addCorp(7000, "health-3");
    health.addCorp(6000, "health-4");

    Industry it;
    it.addIndustry(12000, "it");
    it.addCorp(10000, "Apple");
    it.addCorp(12000, "Microsoft");
    it.addCorp(10000, "Google");
    it.addCorp(2000, "Bethesda");

    for (int i = 0; i < 20; ++i)
    {
        gov.simulate(5, 1, "data2");
        it.simulate(5, 1, "data2");
        health.simulate(5, 1, "data2");
    }
}


/*
#include <vector>
#include <string>
#include <iostream>
#include "DiscreteDistribution.h"
#include "DataGenerator.h"

struct Corporation
{
    std::string name;
    size_t size;
    dd::DiscreteDistribution<> corpFreqs;

    void simulate(size_t n, double p, const std::string& industry, std::ostream& out)
    {
        for (size_t i = 0; i < n; ++i)
        {
            out << industry << "\t" << name << "\t" << size << "\t" << p;
            auto vs = simulate_adversary(corpFreqs.size(), 12 * corpFreqs.size(), 50, 100000000, 50, p);
            for (const auto& v : vs)
            {
                out << "\t" << v.first << "\t" << v.second;
            }
            out << std::endl;
        }
    }
};

struct Industry
{
    void addCorp(size_t size, const std::string& name)
    {
        std::vector<int> sample;
        for (size_t i = 0; i < industryFreq.size() * (size_t)std::sqrt(size); ++i)
            sample.push_back(industryFreq.inverseCdf(entropy.get0_1()));

        Corporation corp;
        corp.name = name;
        corp.size = size;
        corp.corpFreqs = dd::fromFrequency(sample.begin(), sample.end());

        corps.push_back(corp);
    };

    void addIndustry(size_t size, const std::string& name)
    {
        industryFreq = alex::statistics::distributions::discrete_distribution::zipf(size);
        this->name = name;
    };

    void simulate(size_t n, double p, const std::string& filename)
    {
        std::ofstream out(filename, std::ios::app);
        for (auto corp : corps)
        {
            corp.simulate(n, p, name, out);
        }
        out.close();
    };

    size_t totalSize() const
    {
        size_t total = 0;
        for (auto corp : corps)
            total += corp.size;
        return total;
    };

    dd::DiscreteDistribution<> industryFreq;
    std::string name;
    std::vector<Corporation> corps;
};

void makeIndustries(const std::string& filename)
{
    Industry gov;
    gov.addIndustry(14000, "gov");
    gov.addCorp(12000, "NSA");
    gov.addCorp(13000, "IRS");
    gov.addCorp(10000, "DARPA");
    gov.addCorp(9000, "NASA");

    Industry health;
    health.addIndustry(7000, "health");
    health.addCorp(6000, "health-1");
    health.addCorp(8000, "health-2");
    health.addCorp(7000, "health-3");
    health.addCorp(6000, "health-4");

    Industry it;
    it.addIndustry(12000, "it");
    it.addCorp(10000, "Apple");
    it.addCorp(12000, "Microsoft");
    it.addCorp(10000, "Google");
    it.addCorp(2000, "Bethesda");

    for (int i = 0; i < 20; ++i)
    {
        gov.simulate(5, 1, "data2");
        it.simulate(5, 1, "data2");
        health.simulate(5, 1, "data2");
    }
}
*/