#ifndef __BOOTSTRAP_H__
#define __BOOTSTRAP_H__

#include <vector>
#include <random>
#include <functional>

namespace alex { namespace statistics { namespace estimation
{
    template <class T> T quantile(std::vector<T> xs, double p)
    {
        if (p <= 0 || p >= 1)
            throw std::invalid_argument("0 < p < 1");

        size_t offset = (size_t)(p * xs.size());
        auto q = xs.begin(); std::advance(q, offset);
        std::nth_element(xs.begin(), q, xs.end());

        return xs[offset];
    }

    template <class T = double>
    class Bootstrap
    {
    public:
        Bootstrap() {};

        std::vector<T> estimateSamplingDistribution(
            const std::vector<T>& sample,
            std::function<T (const std::vector<T>&)> s,
            size_t sampleSize,
            size_t m)
        {
            auto u = std::uniform_int<>(0, sampleSize - 1);
            std::mt19937 gen;
            std::random_device rd;
            gen.seed(rd());

            std::vector<T> resample(sampleSize);
            std::vector<T> stats; stats.reserve(m);

            for (size_t i = 0; i < m; ++i)
            {
                for (size_t j = 0; j < sampleSize; ++j)
                {
                    resample[j] = sample[u(gen)];
                }
                auto v = s(resample);
                stats.push_back(v);
            }

            std::sort(stats.begin(), stats.end());
            return stats;
        };

        std::pair<T, T> estimate(const std::vector<T>& sample,
                                 std::function<T (const std::vector<T>&)> s,
                                 size_t sampleSize,
                                 size_t m,
                                 T alpha)
        {
            auto u = std::uniform_int<>(0, sample.size() - 1);
            std::mt19937 gen;
            std::random_device rd;
            gen.seed(rd());

            std::vector<T> stats; stats.reserve(m);
            std::vector<T> resample(sample.size());

            for (size_t i = 0; i < m; ++i)
            {
                for (size_t j = 0; j < sample.size(); ++j)
                    resample[j] = sample[u(gen)];

                stats.push_back(s(resample));
            }

            size_t lo = (size_t)std::floor(m * alpha / 2);
            size_t hi = (size_t)std::ceil(m * (1 - alpha / 2) - 1);
            std::nth_element(stats.begin(), stats.begin() + lo, stats.end());
            std::nth_element(stats.begin(), stats.begin() + hi, stats.end());          
            return std::make_pair(stats[lo], stats[hi]);
        };
    };
}}}

#endif