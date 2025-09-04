# Estimating Confidentiality of Encrypted Searches using Moving Average Bootstrap

## Overview

This repository contains the research artifacts for an academic paper on estimating the confidentiality of encrypted database searches using moving average bootstrap methods. The work analyzes how adversaries might infer information from encrypted search patterns and provides statistical methods for quantifying this risk.

## Repository Status

⚠️ **Important**: This repository is preserved for academic transparency and reproducibility. The C++ implementation has missing dependencies (statistical library headers) that prevent direct compilation. See [REPRODUCIBILITY.md](REPRODUCIBILITY.md) for detailed information about what can and cannot be reproduced.

## Paper Abstract

This research presents a methodology for estimating confidence intervals when analyzing the confidentiality of encrypted database searches. Using moving average bootstrap techniques, we model an adversary's ability to map encrypted trapdoors to plaintext terms based on frequency analysis. The bootstrap method provides robust confidence intervals for quantifying information disclosure risks at various accuracy thresholds.

## Key Concepts

- **Trapdoor**: Cryptographically hashed search term that hides the plaintext
- **N\*|p\***: Distribution of trapdoor observations needed to achieve accuracy level p*
- **Moving Average**: Smoothing technique to stabilize accuracy measurements
- **Bootstrap Method**: Statistical resampling technique for confidence interval estimation

## Repository Structure

```
.
├── README.md                  # This file
├── CITATION.cff              # Citation information
├── LICENSE                   # Usage terms
├── REPRODUCIBILITY.md        # Detailed reproducibility information
├── DATA_DICTIONARY.md        # Description of all data files
├── CLAUDE.md                 # Instructions for AI assistants
├── mab.tex                   # LaTeX source of the paper
├── mab.pdf                   # Published paper PDF
├── plots/                    # Data files and visualization outputs
│   ├── cpp/                  # C++ implementation (incomplete dependencies)
│   ├── gnu_plot_code/        # Plotting scripts
│   └── figures/              # Generated figures
├── data_analysis/            # Population data for analysis
└── original_published/       # Original published version
```

## Methodology Summary

1. **Data Generation**: Simulate adversary observing encrypted search queries
2. **Accuracy Tracking**: Monitor proportion p of correctly mapped trapdoors over N observations
3. **Moving Average**: Apply smoothing to get stable accuracy measure p*
4. **Bootstrap Sampling**: Generate confidence intervals for N* at various p* levels
5. **Risk Quantification**: Determine observation thresholds for unacceptable disclosure levels

## Data Files

Key data files include:
- `pop_data`: Population data for bootstrap analysis
- `data_grouped_by_pstar`: Observations organized by accuracy levels
- `quantiles_with_ci`: Bootstrap-generated confidence intervals
- Various `.dat` files: Intermediate analysis results

See [DATA_DICTIONARY.md](DATA_DICTIONARY.md) for detailed descriptions.

## Implementation

The main implementation is in C++ (`plots/cpp/Source.cpp`) with dependencies on a custom statistics library that includes:
- Bootstrap methods
- Empirical distribution functions
- Random variate generation
- Statistical analysis tools

**Note**: The required header files from the `alex::statistics` namespace are not included in this repository, preventing direct compilation.

## Key Results

The analysis provides:
- Confidence intervals for adversary success at different accuracy thresholds
- Quantile estimates for observation requirements
- Risk assessment for encrypted search systems

## Requirements

### For viewing results:
- PDF viewer for the paper
- Text editor for data files

### For attempting reproduction (partial):
- C++ compiler (g++ or equivalent)
- GNU Plot for visualizations
- LaTeX distribution for paper compilation
- **Missing**: Statistical library headers (see REPRODUCIBILITY.md)

## Limitations

1. **Missing Dependencies**: The C++ code cannot be compiled due to missing statistical library headers
2. **Platform Specific**: Visual Studio project files suggest Windows development environment
3. **Incomplete Documentation**: Some implementation details are not fully documented

## Usage

### Viewing the Research
1. Read the paper: `mab.pdf`
2. Examine the methodology: `plots/research_notes.txt`
3. Review data files as described in `DATA_DICTIONARY.md`

### Understanding the Code
1. Main analysis logic: `plots/cpp/Source.cpp`
2. Data analysis functions: `plots/cpp/DataAnalysis.h`
3. Note that compilation will fail due to missing dependencies

## Contributing

This is an archival repository for a published paper. For questions about the methodology or implementation, please contact the authors.

## License

See [LICENSE](LICENSE) file for usage terms.

## Citation

If you use this work in your research, please cite:

```bibtex
@inproceedings{towell2016estimating,
  title={Estimating Confidentiality of Encrypted Searches using Moving Average Bootstrap},
  author={Towell, Alex and Fujinoki, Hiroshi},
  year={2016},
  note={Academic publication - specific venue to be added}
}
```

For the complete citation information, see [CITATION.cff](CITATION.cff).

## Contact

For questions about this research or the methodology, please open an issue in this repository.

---

*This repository is maintained for academic reproducibility and transparency purposes.*