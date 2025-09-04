# Data Dictionary

This document describes the data files in the repository and their formats.

## Main Data Files

### Population and Sample Data

#### `pop_data` (plots/ and data_analysis/)
- **Size**: 883,243 bytes
- **Description**: Population data used for bootstrap analysis
- **Format**: Tab-separated values containing N* observations for different p* accuracy levels
- **Usage**: Primary input for bootstrap confidence interval estimation

#### `data_grouped_by_pstar`
- **Size**: 394,796 bytes
- **Description**: Experimental observations organized by accuracy threshold levels
- **Format**: Groups of N* values for each p* level (0.15, 0.175, 0.2, ..., 0.5)
- **Usage**: Intermediate data for quantile analysis

### Accuracy Analysis Files

#### `all_pstars`
- **Description**: Summary of all p* accuracy levels tested
- **Format**: List of p* values from 0.15 to 0.5 in increments of 0.025

#### `data_pstar_vs_nstar`
- **Description**: Mapping between accuracy levels (p*) and observation counts (N*)
- **Format**: Two columns: p* value, corresponding N* value

#### `pstar=0.3_vs_nstar`
- **Description**: Specific analysis for p* = 0.3 accuracy level
- **Usage**: Example case study for 30% accuracy threshold

### Confidence Interval Files

#### `quantiles_with_ci`
- **Description**: Bootstrap-generated quantiles with confidence intervals
- **Format**: Quantile values with lower and upper confidence bounds
- **Usage**: Primary results showing uncertainty estimates

#### `quantiles_with_ci_2`
- **Description**: Alternative confidence interval calculations
- **Format**: Similar to above, possibly using different bootstrap parameters

### Visualization Data Files

#### `figure_2a.dat`
- **Description**: Data for Figure 2a in the paper
- **Format**: X,Y coordinates for plotting

#### `figure_2b.dat`
- **Description**: Data for Figure 2b in the paper
- **Format**: X,Y coordinates for plotting

#### `figure_3_2.dat`
- **Description**: Data for Figure 3.2 in the paper
- **Format**: Plotting coordinates

#### `compare_zipf_encrypted_versus_plain.dat`
- **Description**: Comparison of Zipf distribution for encrypted vs plaintext
- **Format**: Two sections - plaintext frequencies and encrypted frequencies
- **Usage**: Demonstrates frequency analysis attack potential

#### `histo.dat`
- **Description**: Histogram data for distribution visualization
- **Format**: Bin values and frequencies

### Generated Figures

#### `fig8a.png`, `fig8b.png`, `fig8c.png`
- **Description**: Generated plots showing bootstrap analysis results
- **Format**: PNG images
- **Usage**: Visual representation of confidence intervals at different p* levels

### Auxiliary Files

#### `pstars`
- **Size**: 2,536 bytes
- **Description**: Extended list of p* values used in analysis
- **Format**: Single column of accuracy threshold values

#### `sample_data_pdf`
- **Description**: Probability density function of sample data
- **Format**: PDF values for visualization

#### `pop_data_pdf`
- **Description**: Probability density function of population data
- **Format**: PDF values for comparison with sample

#### `tmp`
- **Size**: 786,984 bytes
- **Description**: Temporary working file (likely intermediate calculations)
- **Note**: May not be essential for reproduction

## Data Formats

### Common Format Patterns

1. **Tab-separated values (TSV)**: Most data files use tabs as delimiters
2. **Column headers**: Generally absent (data starts immediately)
3. **Numeric precision**: Floating point values with varying decimal places
4. **Line breaks**: Unix-style (LF) line endings

### Reading the Data

Example for reading in Python:
```python
import pandas as pd
import numpy as np

# For simple two-column files
data = pd.read_csv('data_pstar_vs_nstar', sep='\t', header=None, 
                   names=['p_star', 'n_star'])

# For grouped data
with open('data_grouped_by_pstar', 'r') as f:
    content = f.read()
    # Parse groups separated by double newlines
```

Example for reading in R:
```r
# For tab-separated files
data <- read.table('data_pstar_vs_nstar', sep='\t', 
                   col.names=c('p_star', 'n_star'))

# For grouped data
lines <- readLines('data_grouped_by_pstar')
# Process groups based on empty lines
```

## Data Generation Process

The data files represent various stages of the analysis pipeline:

1. **Initial simulation** → generates raw observations
2. **Grouping by p*** → organizes by accuracy levels (`data_grouped_by_pstar`)
3. **Bootstrap sampling** → creates distributions from empirical CDF
4. **Quantile extraction** → produces confidence intervals (`quantiles_with_ci`)
5. **Visualization** → generates plot data files (`figure_*.dat`)

## Missing Data Context

Some context about data generation is embedded in the missing C++ code:
- Simulation parameters (number of iterations, random seeds)
- Exact bootstrap implementation details
- Smoothing window parameters for moving average

## Notes for Researchers

- **Reproducibility**: While exact regeneration of data requires missing code, the preserved data files allow validation of alternative implementations
- **Statistical validity**: Bootstrap sample sizes and confidence levels can be inferred from data dimensions
- **Visualization**: GNU Plot scripts in `plots/gnu_plot_code/` may provide additional context for data interpretation

---

*For questions about specific data files or formats, please refer to the paper or open an issue in the repository.*