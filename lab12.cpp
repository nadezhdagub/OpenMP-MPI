#include <vector>
#include <random>
#include <string>
#include <cmath>
#include <functional>

#include <mpi.h>
#include <iostream>

constexpr int MIN_A = -5;
constexpr int MAX_A = 5;

std::vector<int> fillVector(const std::size_t size, int min, int max) {
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_int_distribution<int> dist(min, max);

  std::vector<int> vector(size);
  for (int i = 0; i < size; i++) {
    vector[i] = dist(mt);
  }
  return vector;
}

std::string getOption(char *argv[], const int argc, const std::string &option, const std::string &def) {
  for (int i = 1; i < argc - 1; i++) {

    if (option == argv[i]) {
      return argv[i + 1];
    }
  }
  return def;
}

double q(const int i, const int r, const std::vector<double> &xPows, const std::vector<int> &a) {
  double value = 0;
  for (int j = 0, k = (i - 1) * r + 1; j < r; j++, k++) {
    value += a[k] * xPows[j];
  }
  return value;
}

template<typename T>
void blockCount(int rank, int blockSize, std::vector<T> &vectorToFill,
                const std::function<T(int)> &function) {
  for (int i = 0; i < blockSize; i++) {
    int index = rank * blockSize + i;
    if (index >= vectorToFill.size()) {
      break;
    }
    vectorToFill[index] = function(i);
  }
}

int main(int argc, char **argv) {


  const int r = std::stoi(getOption(argv, argc, "-r", "2"));
  const double x = std::stod(getOption(argv, argc, "-x", "1.2"));
  const int s = std::pow(2, r);
  const std::vector<int> a = fillVector(r * s, MIN_A, MAX_A);


  int rank = 0, size = 0;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  std::vector<double> xPows(r + 1);
  xPows[0] = 1;
  for (int i = 1; i < r; i++) {
    xPows[i] = x * xPows[i - 1];
  }

  std::vector<double> qi(s - 1);
  int blockSize = std::ceil(s - 1 / size);

  blockCount<double>(rank, blockSize, qi, [&](int i) { return q(i + 1, r, xPows, a); });

  std::vector<double> xr(s - 2);
  for (int i = 0; i < s - 2; ++i) {
    xr[i] = std::pow(x, r * (i + 1));
  }

  std::vector<double> multiples(s - 2);
  int blockSize2 = std::ceil(s - 2 / size);
  blockCount<double>(rank, blockSize2, multiples, [&](int i) { return xr[i] * qi[i + 1]; });

  double sum = a[0] + qi[0];
  for (double multiple : multiples) {
    sum += multiple;
  }
  std::cout << "sum = " << sum << "\n";
  MPI_Finalize();
  return 0;
}
