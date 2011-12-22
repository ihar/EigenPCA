#include <iostream>
#include <iomanip>
#include <iterator>

#include "pca.h"

using namespace std;

int main() {
  unsigned int n = 10;  // Number of cases
  unsigned int m = 6;  // Number of vars
  static const float arr[] = { // A data matrix row by row
                2.5, 1.5, 2.4, 0.5, 5, 1,
                0.5, 1.5,  0.7, 2.9, 0.9,  1,
                2.2, 1.5,  2.9, 1.2, 1.2, 1,
                1.9, 1.5,  2.2, 3.4, 2.0, 1,
                3.1, 1.5,  3.0, 2.9, 3.2, 1,
                2.3, 1.5,  2.7, 4.3, 1.1, 1,
                2, 1.5,  1.6, 2.4, 2.5, 1,
                1, 1.5,  1.1, 1.1, 2.1, 1,
                1.5, 1.5,  1.6, 3.5, 2.0, 1,
                1.1, 1.5,  0.9, 0.9, 0.8, 1};
  vector<float> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));

  Pca *pca = new Pca();
  int init_result = pca->Calculate(vec, n, m);//, true, true, false);
  if (0 != init_result) {
    cerr << "There is an error during PCA calculation!" << endl;
    return -1;
  }

  vector<float> sd = pca->sd(),
                prop_of_var = pca->prop_of_var(), 
                cum_prop = pca->cum_prop(), 
                scores = pca->scores();
  vector<unsigned int> el_cols = pca->eliminated_columns();
  float         kaiser = pca->kaiser(), 
                thresh95 = pca->thesh95();
  unsigned int
                ncols = pca->ncols(),
                nrows = pca->nrows();
  string 
                method = pca->method();
  delete pca;

  cout << "Initial matrix: " << endl;
  for (unsigned int i = 0; i < n; ++i) {
    for (unsigned int j = 0; j < m; ++j) {
      cout << setw(7) << vec[j + m*i];
    }
    cout << endl;
  }
  if (0 != el_cols.size()) {
    cout << "\nNumbers of eliminated columns (0 based):\n";
    copy(el_cols.begin(), el_cols.end(), std::ostream_iterator<unsigned int>(std::cout," "));  
    cout << "\n\nMatrix after the eliminating: " << endl;
    for (unsigned int i = 0; i < n; ++i) {
      for (unsigned int j = 0; j < m; ++j) {
        if ( find(el_cols.begin(), el_cols.end(), j) == el_cols.end() ) {
          cout << setw(7) << vec[j + m*i];
        }
      }
      cout << endl;
    }
  }
  cout << "\n\n" << method << " mathod was used\n";
  cout << "\n\nStandard deviation:\n";
  copy(sd.begin(), sd.end(), std::ostream_iterator<float>(std::cout," "));  
  cout << "\n\nProportion of variance:\n";
  copy(prop_of_var.begin(), prop_of_var.end(), std::ostream_iterator<float>(std::cout," "));  
  cout << "\n\nCumulative proportion:\n";
  copy(cum_prop.begin(), cum_prop.end(), std::ostream_iterator<float>(std::cout," "));  
  cout << "\n\nKaiser criterion: " << kaiser;
  cout << "\n\n95% threshold criterion: " << thresh95 << endl;

  cout << "\n\nRotated data: " << endl;
  for (unsigned int i = 0; i < nrows; ++i) {
    for (unsigned int j = 0; j < ncols; ++j) {
      cout << setw(13) << scores[j + ncols*i];
    }
    cout << endl;
  }
  return 0;
}