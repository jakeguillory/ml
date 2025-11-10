# Machine Learning Algorithms in C

A collection of simple implementations of some core machine learning algorithms, written in C for educational purposes.


## Implemented Models

| Model | Description |
|--------|--------------|
| **Linear Regression** | Fits a straight line to data using gradient descent. |
| **Perceptron** | Basic neural network unit with step activation for binary classification. |
| **Logistic Regression** | Classifies probabilistic outcomes with sigmoid activation. |
| **Naive Bayes** | Text classification model (spam/ham detector) using word frequency tables. |
---

##  Project Goals

- Learn the fundamental priniciples of ML by implementing them from scratch.
- Advance C programming skills.
- Create useful command line tools for initial data exploration in ML workflows.

---

## Building

```bash
make            # Builds all models into respective folders
make clean      # Removes binaries
```

## Running

Linear Regression

```bash
cd lin_reg
./lin_reg -e 1000 -l 0.01 < data
```

Perceptron

```bash
cd perceptron
./perceptron -e 1000 -l 0.01 < data
```

Logistic Regression

```bash
cd log_reg
./log_reg -e 1000 -l 0.01 < data
```

Naive Bayes

```bash
cd naive
./naive -s "This string will be classified" < word_counts
```
