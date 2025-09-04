# Reproducibility Information

## Overview

This document provides detailed information about the reproducibility of the research presented in "Estimating Confidentiality of Encrypted Searches using Moving Average Bootstrap". While the repository preserves the original research artifacts, complete reproduction is limited due to missing dependencies.

## What Can Be Reproduced

### 1. Paper and Documentation
- **Full Paper**: The complete LaTeX source (`mab.tex`) and compiled PDF (`mab.pdf`) are available
- **Methodology**: The theoretical approach is fully documented in `plots/research_notes.txt`
- **Data Analysis**: Output data files show the results of the original analysis

### 2. Conceptual Understanding
- Bootstrap methodology for confidence interval estimation
- Moving average approach for stability analysis
- Statistical framework for adversary modeling

### 3. Data Inspection
- All generated data files are preserved and can be examined
- Intermediate results show the progression of analysis
- Final quantiles and confidence intervals are available

## What Cannot Be Reproduced

### 1. Code Execution
The C++ implementation cannot be compiled due to missing dependencies:

#### Missing Header Files
```cpp
// From alex::statistics namespace (not included):
- RandomVariates.h       // Random number generation
- Bootstrap.h            // Bootstrap implementation
- EmpiricalDistribution.h // Empirical CDF construction
- BarGraph.h            // Visualization components
- Entropy.h             // Entropy calculations
- StatTools.h           // Statistical utilities
- DiscreteDistribution.h // Discrete probability distributions
- Histogram.h           // Histogram generation
```

These appear to be from a custom or proprietary statistics library that was available in the original development environment but is not included in this repository.

### 2. Complete Build Environment
- Original development used Visual Studio on Windows (`.vcxproj` file present)
- No cross-platform build configuration provided
- Specific compiler versions and flags unknown

## Original Computing Environment

Based on available evidence:
- **Operating System**: Windows (Visual Studio project files)
- **IDE**: Microsoft Visual Studio
- **Language**: C++ (likely C++11 or later based on code style)
- **Additional Tools**: GNU Plot for visualization
- **Custom Library**: alex::statistics (not publicly available)

## Missing Dependencies Details

### Statistical Library (alex::statistics)

The core functionality depends on a namespace `alex::statistics` which provides:

1. **Random Variate Generation**
   - Uniform random numbers
   - Distribution sampling

2. **Bootstrap Methods**
   - Resampling with replacement
   - Confidence interval construction

3. **Distribution Functions**
   - Empirical CDF construction
   - Quantile estimation
   - Discrete distributions (including Zipf)

4. **Visualization**
   - Histogram generation
   - Bar graphs
   - Data plotting utilities

## Suggested Alternatives for Reimplementation

If you wish to reimplement this research, consider these modern alternatives:

### C++ Libraries
- **Boost.Math**: Statistical distributions and functions
- **GSL (GNU Scientific Library)**: Random number generation, statistics
- **Armadillo**: Linear algebra and statistics
- **matplotlib-cpp**: For plotting (wrapper around Python's matplotlib)

### Python Implementation
A Python reimplementation might be more accessible:
```python
# Suggested Python libraries:
import numpy as np           # Numerical computing
import scipy.stats          # Statistical functions
import pandas as pd         # Data manipulation
from scipy.stats import bootstrap  # Bootstrap methods
import matplotlib.pyplot as plt    # Visualization
```

### R Implementation
R provides excellent built-in support for bootstrap methods:
```r
# Suggested R packages:
library(boot)      # Bootstrap functions
library(ggplot2)   # Visualization
library(dplyr)     # Data manipulation
```

## Key Algorithms to Reimplement

### 1. Moving Average Calculation
```
For each observation n:
  - Track accuracy p(n) = correct_mappings / n
  - Apply smoothing window to get p*(n)
  - Record when p* crosses thresholds
```

### 2. Bootstrap Confidence Intervals
```
Given sample of N* values for accuracy p*:
  1. Create empirical CDF from sample
  2. Resample with replacement (size M)
  3. Calculate quantile of interest
  4. Repeat k times
  5. Use percentile method for CI
```

### 3. Quantile Estimation
```
For each p* level (0.25, 0.3, ..., 0.6):
  - Generate distribution of N* values
  - Apply bootstrap for CI estimation
  - Report quantiles (5th, 50th, 95th percentile)
```

## Data Generation Process

The original data generation involved:
1. Simulating encrypted search queries with Zipf distribution
2. Adversary attempting frequency analysis attack
3. Recording accuracy over time
4. Applying moving average smoothing
5. Bootstrap sampling for confidence intervals

## Validation Approach

To validate a reimplementation:
1. Compare output distributions with provided data files
2. Verify confidence interval widths are similar
3. Check that quantile estimates match within statistical error
4. Ensure moving average behavior is consistent

## Known Limitations

1. **Random Seed**: Original random seed not documented
2. **Parameter Values**: Some simulation parameters may be embedded in missing code
3. **Exact Algorithms**: Specific implementation details of bootstrap method unclear
4. **Convergence Criteria**: Stopping conditions for simulations not fully documented

## Recommendations for Researchers

### If you want to understand the methodology:
1. Read the paper (`mab.pdf`)
2. Study the research notes (`plots/research_notes.txt`)
3. Examine the data files to understand output format

### If you want to reimplement:
1. Start with the mathematical description in research notes
2. Use modern statistical libraries (see alternatives above)
3. Validate against provided data files
4. Consider publishing your reimplementation for others

### If you want to extend this work:
1. Consider modern privacy metrics beyond frequency analysis
2. Apply to current encrypted database systems
3. Explore different bootstrap variations
4. Test with real-world query distributions

## Contact for Clarification

For questions about specific implementation details not covered here, please:
1. Open an issue in this repository
2. Contact the original authors (see CITATION.cff)
3. Consult the published paper for theoretical details

## Reproducibility Checklist

- [x] Paper and documentation available
- [x] Theoretical methodology described
- [x] Output data preserved
- [x] Main source code included
- [ ] All dependencies available
- [ ] Build instructions complete
- [ ] Random seeds documented
- [ ] Full parameter sets specified

## Statement on Reproducibility

This repository represents a best-effort preservation of research artifacts from 2016. While complete computational reproducibility is not possible due to missing dependencies, the theoretical contribution and methodology are fully documented. The preserved data files allow for validation of reimplementations and the source code structure provides insight into the original implementation approach.

---

*Last updated: Current repository state as preserved for archival purposes*