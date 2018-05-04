// ASSUMPTION : WHILE CALCULATING CURRENT ACCROSS THE ELEMENTS WE ARE
// CONSIDERING ONLY A FREQUENCY WHICH EVER OCCURS FIRST IN THE INSTRUCTIONS .
/////////////////////////////////
//   INBUILT HEADERS REQUIRED  //
/////////////////////////////////
#include <iostream>
#include <regex>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <sstream>
#include <algorithm>
#include <complex>
#include <eigen3/Eigen/Dense>  //EIGEN HEADER REQUIRED FOR INVERSE CALCULATION OF MATRIX

////////////////////////////////
//        HEADERS INCLUDED    //
////////////////////////////////
#include "solve.h"
#include "main.h"

using namespace Eigen;
using namespace std;

/////////////////////////////////////////////////////////////////////////////
//                           SOLVE CIRCUIT FUNCTION                        //
/////////////////////////////////////////////////////////////////////////////
/*
-----------------DESCRIPTION ABOUT THIS FUNCTION-----------------------------
THIS FUNCTION ACCEPTS TWO ARGUMENTS i.e. VALUE AND DATA .BOTH ARE OF VECTOR
TYPE.
DATA :- THIS CONTAINS THE PARSE DATA IN THE FORM OF STRINGS WHICH WE PARSED IN
MAIN.CPP.
VALUE :- THIS CONTAINS THE PARSE DATA IN THE FORM OF INTEGER VALUE SO THAT WE
CAN DO THE CALCULATION REQUIRED FOR SOLVING IT.


*/
string solve_circuit(vector<double> value[], vector<string> data[], int index) {
  int x[(2 *
         index)];  // ARRAY WHICH IS MADE TO CONTAIN DISTINCT NUMBER OF NETS.

  for (int i = 0; i < index; i++) {
    x[i] = (int)(value[2][i]);  // 2ND INDEX OF VALUE CONTAINS FIRST NETS
                                // CONNECTION .
  }
  int j = index;
  for (int i = 0; i < index; i++) {
    x[j] = (int)(value[3][i]);
    j++;  // 3RD INDEX OF VALUE ARRAY CONTAINS SECOND NETS CONNECTION.
  }
  sort(x, x + (2 * index));  // TO DETERMINE DISTINCT NETS OCCURING OR NOT.

  for (int i = 0; i < (2 * index - 1); i++) {
    if (x[i + 1] == x[i])
      x[i] = 10007;  // INDEX WHICH ARE NOT REQUIRED OR EXTRA ARRAY SPACES ARE
                     // HAVING A DEFAULT VALUE OF 10007.
  }
  sort(x, x + (2 * index));  // NOW SORTING IN INCREASING ORDER TO DETERMINE THE
                             // DISTINCT NETS.

  int size = 0, flag = 0;
  for (int i = 0; i < (2 * index); i++) {
    // cout<<x[i]<<" ";
    if ((x[i] == 10007) && (flag == 0)) {
      size = i;  // SIZE TO FIND THE NO. OF DISTINCT NETS WE HAVE.
      flag = 1;
    }
  }

  int m = 0,
      n = 0;  // N AND M WILL CONTAIN AN INTEGER WHICH WILL DETERMINE THE NO. OF
  // INDEPENDENT CURRENT SOURCES AND VOLTAGE SOURCES RESPECTIVELY.
  for (int i = 0; i < index; i++) {
    if (value[0][i] == 3) m++;  // CALCULATING DISTINCT VOLTAGE SOURCES.
  }

  for (int i = 0; i < index; i++) {
    if (value[0][i] == 4) n++;  // CONTAINING DISTINCT CURRENT SOURCES.
  }
  double freq[m + n];  // IT WILL CONTAIN FREQUENCIES OF INDEPENDENT SOURCES.
  int k = 0;
  for (int i = 0; i < index; i++) {
    if (value[0][i] == 3) {
      freq[k] = value[7][i];
      k++;  // COPING FREQUENCY FROM VALUE TO FREQ VARIABLE FOR VOLTAGE SOURCES.
    }
  }

  for (int i = 0; i < index; i++) {
    if (value[0][i] == 4) {
      freq[k] = value[7][i];
      k++;  // COPING FREQUENCY FROM VALUE TO FREQ VARIABLE FOR CURRENT SOURCES.
    }
  }
  double voltage[m + n][size + 1][size + 1];  // IT WILL CONTAIN REAL
                                              // COFFICIENTS OF PASSIVE ELEMENTS
  // AND IT IS A (m+n)X(N+1)X(N+1) MATRIX WHERE N IS THE NO. OF NETS.
  // m AND n ARE THE NO. OF INDEPENDENT SOURCES.
  for (int k = 0; k < m + n; k++) {
    for (int i = 0; i < size + 1; i++) {
      for (int j = 0; j < size + 1; j++) {
        voltage[k][i][j] = 0;  // INITIALIZATION OF VOLTAGE VARIABLE.
      }
    }
  }
  k = 1;
  for (int g = 0; g < m + n; g++) {
    k = 1;
    for (int i = 1; i < size; i++) {
      voltage[g][i][0] = x[k];
      k++;  // PROVIDING NETS TO THE 0TH ROW OF THE VOLTAGE MATRIX.
    }
  }
  k = 1;
  // voltage[size][0]=-1;
  for (int g = 0; g < m + n; g++) {
    k = 1;
    for (int i = 1; i < size; i++) {
      voltage[g][0][i] = x[k];
      k++;  // PROVIDING NETS TO THE 0TH COLUMN OF VOLTAGE MATRIX.
    }
  }

  for (int g = 0; g < m + n; g++) {
    for (int i = 1; i < size; i++) {
      for (int j = 0; j < index; j++) {
        if (((value[2][j] == voltage[g][i][0]) ||
             (value[3][j] == voltage[g][i][0])) &&
            (value[0][j] == 0)) {
          if (value[2][j] == voltage[g][i][0]) {
            double r;  // THIS VARIABLE IS USED FOR CALCULATING COFFIECIENTS OF
                       // THE SOURCES.
            r = 1 / value[4][j];
            voltage[g][i][i] += r;
            for (int k = 1; k < size + 1; k++) {
              if (voltage[g][0][k] == value[3][j]) {
                voltage[g][i][k] =
                    (-1 *
                     r);  // REAL COFFICIENTS BEING COPIED TO VOLTAGE MATRIX.
              }
            }
          }
          if (value[3][j] == voltage[g][i][0]) {
            double r;
            r = 1 / value[4][j];
            voltage[g][i][i] += r;
            for (int k = 1; k < size + 1; k++) {
              if (voltage[g][0][k] == value[2][j]) {
                voltage[g][i][k] =
                    (-1 *
                     r);  // REAL COFFICIENTS BEING COPIED TO VOLTAGE MATRIX.
              }
            }
          }
        }
      }
    }
  }
  double pie = 3.14;  // CONSTANT VARIABLE
  double imvoltage[m + n][size + 1][size + 1];  // IT WILL CONTAIN IMAGINARY
                                                // COFFICIENTS OF PASSIVE
                                                // ELEMENTS
  // AND IT IS A (m+n)X(N+1)X(N+1) MATRIX WHERE N IS THE NO. OF NETS.
  // m AND n ARE THE NO. OF INDEPENDENT SOURCES.
  for (int g = 0; g < m + n; g++) {
    for (int i = 0; i < size + 1; i++) {
      for (int j = 0; j < size + 1; j++) {
        imvoltage[g][i][j] = 0;  // INITIALIZATION OF IMVOLTAGE MATRIX
      }
    }
  }
  k = 1;
  for (int g = 0; g < m + n; g++) {
    k = 1;
    for (int i = 1; i < size; i++) {
      imvoltage[g][i][0] = x[k];
      k++;  // PROVIDING NETS TO THE 0TH ROW OF THE IMVOLTAGE MATRIX.
    }
  }
  k = 1;
  // imvoltage[size][0]=-1;
  for (int g = 0; g < m + n; g++) {
    k = 1;
    for (int i = 1; i < size; i++) {
      imvoltage[g][0][i] = x[k];
      k++;  // PROVIDING NETS TO THE 0TH COLUMN OF THE IMVOLTAGE MATRIX.
    }
  }

  for (int g = 0; g < m + n; g++) {
    for (int i = 1; i < size; i++) {
      for (int j = 0; j < index; j++) {
        if (((value[2][j] == imvoltage[g][i][0]) ||
             (value[3][j] == imvoltage[g][i][0])) &&
            ((value[0][j] == 1) || (value[0][j] == 2))) {
          if (value[0][j] == 1) {
            if (value[2][j] == imvoltage[g][i][0]) {
              double r;
              r = ((-1) * (2 * pie * freq[g] * value[4][j]));
              imvoltage[g][i][i] += r;
              for (int k = 1; k < size + 1; k++) {
                if (imvoltage[g][0][k] == value[3][j]) {
                  imvoltage[g][i][k] = (-1 * r);  // IMAGINARY COFFICIENTS BEING
                                                  // COPIED TO IMVOLTAGE MATRIX.
                }
              }
            }
            if (value[3][j] == imvoltage[g][i][0]) {
              double r;
              r = ((-1) * (2 * pie * freq[g] * value[4][j]));
              imvoltage[g][i][i] += r;
              for (int k = 1; k < size + 1; k++) {
                if (imvoltage[g][0][k] == value[2][j]) {
                  imvoltage[g][i][k] = (-1 * r);  // IMAGINARY COFFICIENTS BEING
                                                  // COPIED TO IMVOLTAGE MATRIX.
                }
              }
            }

          }

          else {
            if (value[2][j] == imvoltage[g][i][0]) {
              double r;  // THIS VARIABLE IS USED FOR CALCULATING COFFIECIENTS
                         // OF THE SOURCES.
              r = 1 / (2 * pie * freq[g] * value[4][j]);
              imvoltage[g][i][i] += r;
              for (int k = 1; k < size + 1; k++) {
                if (imvoltage[g][0][k] == value[3][j]) {
                  imvoltage[g][i][k] = (-1 * r);  // IMAGINARY COFFICIENTS BEING
                                                  // COPIED TO IMVOLTAGE MATRIX.
                }
              }
            }
            if (value[3][j] == imvoltage[g][i][0]) {
              double r;  // THIS VARIABLE IS USED FOR CALCULATING COFFIECIENTS
                         // OF THE SOURCES.
              r = 1 / (2 * pie * freq[g] * value[4][j]);
              imvoltage[g][i][i] += r;
              for (int k = 1; k < size + 1; k++) {
                if (imvoltage[g][0][k] == value[2][j]) {
                  imvoltage[g][i][k] = (-1 * r);  // IMAGINARY COFFICIENTS BEING
                                                  // COPIED TO IMVOLTAGE MATRIX.
                }
              }
            }
          }
        }
      }
    }
  }

  double b[size + 1][m + 1];
  int r = 1;
  k = 1;

  for (int i = 0; i < size + 1; i++) {
    for (int j = 0; j < m + 1; j++) {
      b[i][j] =
          0;  // CONTAINS  1s,-1s AND 0s ONLY, MATRIX FOR VOLTAGE TERMINAL SIGN.
    }
  }
  for (int i = 1; i < size; i++) {
    b[i][0] = x[k];
    k++;
  }

  for (int i = 0; i < index; i++) {
    if (value[0][i] == 3) {
      b[0][r] = value[1][i];
      b[(int)(value[2][i])][r] =
          1;  // SIGN IS BEING DETERMINED HERE FOR INDEPENDENT VOLTAGE SOURCES.
      b[(int)(value[3][i])][r] = -1;
      r++;
    }
  }
  double c[m + 1][size + 1];

  for (int i = 0; i < size + 1; i++) {
    for (int j = 0; j < m + 1; j++) {
      c[j][i] =
          b[i][j];  // C OVER IS HERE IS NOTHING BUT TRANSPOSE OF B MATRIX.
    }
  }

  k = 1;
  double z[size + m - 1][2];  // bekar
  for (int i = 0; i < size + m - 1; i++) {
    for (int j = 0; j < 2; j++) {
      z[i][j] = 0;  // Z IS CONTAINS VALUES OF VOLTAGES AND CURRENT AND IT IS A
                    // 2X(N+M) MATRIX. N AND M
      // ARE DEFINED ABOVE.
    }
  }

  for (int i = 0; i < size - 1; i++) {
    z[i][0] = x[k];
    k++;
    for (int j = 0; j < index; j++) {
      if (value[0][j] == 4) {
        if (z[i][0] == value[2][j])
          z[i][1] += value[6][j];  // AMPLITUDE OF CURRENT SOURCES ARE BEING
                                   // TRANSFERED TO Z MATRIX.
        if (z[i][0] == value[3][j]) z[i][1] += (value[6][j] * (-1));
      }
    }
  }
  k = 1;
  for (int i = size - 1; i < size + m - 1; i++) {
    z[i][0] = c[k][0];
    k++;
    for (int j = 0; j < index; j++) {
      if (value[0][j] == 3) {
        if (z[i][0] == value[1][j])
          z[i][1] += value[6][j];  // AMPLITUDE OF VOLTAGE SOURCES ARE BEING
                                   // TRANSFERED TO Z MATRIX.
      }
    }
  }

  MatrixXcd B(size + m - 1, 1);  // MatrixXcd is a data type defined under eigen
                                 // header required to do complex matrix
                                 // calculations.

  // AS THE NAME SUGGEST A IS THE COFFIECIENT MATRIX , AINV WILL CONTAIN ITS
  // INVERSE AND FINALLY X WILL BE CALCULATED BY CALCULATING AINV*B.
  MatrixXcd A(size + m - 1, size + m - 1), Ainv(size + m - 1, size + m - 1),
      X(size + m - 1, 1), Result(size + m - 1, m + n);
  if (m != 0) {
    for (int i = 1; i < size; i++) {
      for (int j = 1; j < m + 1; j++) {
        A(i - 1, size + j - 2) = {
            b[i][j],
            0};  // COPING DATA INTO A MATRIX TO PERFORM COMPLEX INFORMATION.
      }
    }

    for (int i = 1; i < m + 1; i++) {
      for (int j = 1; j < size; j++) {
        A(i + size - 2, j - 1) = {
            c[i][j],
            0};  // COPING DATA INTO A MATRIX TO PERFORM COMPLEX INFORMATION.
      }
    }

    for (int i = size; i < size + m - 1; i++) {
      for (int j = size; j < size + m - 1; j++) {
        A(i, j) = {0, 0};  // INTIALIZING REST PART OF A MATRIX WITH 0+0i VALUE.
      }
    }
  }
  for (int g = 0; g < m + n;
       g++) {  // double MagX[size+m-1][1],ArgX[size+m-1][1];

    for (int i = 0; i < size + m - 1; i++) {
      B(i, 0) = {
          z[i][1],
          0};  // COPING DATA INTO A MATRIX TO PERFORM COMPLEX INFORMATION.
    }

    for (int i = 1; i < size; i++) {
      for (int j = 1; j < size; j++) {
        A(i - 1, j - 1) = {voltage[g][i][j],
                           imvoltage[g][i][j]};  // COPING DATA INTO A MATRIX TO
                                                 // PERFORM COMPLEX INFORMATION.
        // AS DETERMINED ABOVE VOLTAGE MATRIX CONTAINS REAL PART OF COFFICIENTS
        // AND IMVOLTAGE MATRIX CONTAINS IMAGINARY PART OF COFFICIENTS.
      }
    }

    Ainv = A.inverse();  // CACLUTLATING A INVERSE BY CALLING AN INBUILT
                         // FUNCTION DEFINED IN EIGEN HEADER.

    X = Ainv * B;  // FINALLY CALCULATING X  WHICH CONTAINS VOLTAGES AT EACH NET
                   // AND LOWER PART OF MATRIX CONTAINS CURRENT IN VOLTAGE
                   // SOURCES.

    for (int i = 0; i < size + m - 1; i++)
      Result(i, g) = X(i, 0);  // SINCE X IS FOR A PERTICULAR AC SOURCE AND FOR
                               // A PERTICULAR FREQUENCY , WE NEED TO STORE IT
                               // THATS WHY WE
                               // MADE A RESULT MATRIX TO STORE IT.
  }

  string s = "";
  for (int g = 0; g < m + n; g++) {
    MatrixXcd answer(2, index);  // THIS WILL CONTAIN FINAL RESULT i.e. VOLTAGES
                                 // AND CURRENTS ACCROSS THE ELEMENTS OF THE
                                 // CIRCUIT .

    complex<double> f1(0, 0), f2(0, 0);  // TEMPORARY COMPLEX VARIABLES.
    int pos1 = 0, pos2;
    for (int i = 0; i < index; i++) {
      for (int j = 1; j < size; j++) {
        if ((value[2][i] == voltage[0][j][0]) && (value[2][i] != -1))
          pos1 = j -
                 1;  // DETERMINING INDEX TO WHICH A PERTICULAR NET CORRESPONDS.
        if (value[2][i] == -1)
          pos1 =
              -15;  // DETERMINING INDEX TO WHICH A PERTICULAR NET CORRESPONDS.
      }

      for (int j = 1; j < size; j++) {
        if ((value[3][i] == voltage[0][j][0]) && (value[3][i] != -1))
          pos2 = j -
                 1;  // DETERMINING INDEX TO WHICH A PERTICULAR NET CORRESPONDS.
        if (value[3][i] == -1)
          pos2 =
              -15;  // DETERMINING INDEX TO WHICH A PERTICULAR NET CORRESPONDS.
      }
      f1 = {0, 0};
      f2 = {0, 0};
      // WE REQUIRE NOW POTENTIAL DIFFENCE ACCROSS THE ELEMENTS SINCE WE HAVE
      // SUCCESSIVELY FIND THE
      // NET TO WHICH IT IS CONNECTED. WE JUST NOW NEED TO SUBTRACT IT's
      // POTENTIAL VALUES WHICH IS
      // STORED IN RESULT MATRIX.

      if ((pos1 != -15) &&
          (pos2 !=
           -15))  // -15 IS LIKE A FLAG WHICH STATES THAT IT IS CONNECTED TO
      {
        f1 = Result(pos1, g);
        f2 = Result(pos2, g);
      } else if ((pos1 == -15) && (pos2 == -15)) {
        f1 = {0, 0};  // POSSIBILITY FOR CONNECTION WITH EARTHING
        f2 = {0, 0};  // POSSIBILITY FOR CONNECTION WITH EARTHING
      } else if ((pos1 != -15) && (pos2 == -15))  // -15 IS LIKE A FLAG WHICH
                                                  // STATES THAT IT IS CONNECTED
                                                  // TO EARTHING.
      {
        f1 = Result(pos1, g);
        f2 = {0, 0};  // POSSIBILITY FOR CONNECTION WITH EARTHING
      } else if ((pos1 == -15) && (pos2 != -15))  // -15 IS LIKE A FLAG WHICH
                                                  // STATES THAT IT IS CONNECTED
                                                  // TO
      {
        f1 = {0, 0};  // POSSIBILITY FOR CONNECTION WITH EARTHING
        f2 = Result(pos2, g);
      }

      answer(0, i) = f1 - f2;  // FINALLY POTENTIAL DIFFENCE OF ELEMENTS ARE
                               // COMPUTED BY SUBTRACTING NET POTENTIALS
    }

    MatrixXcd impedence(1, index);  // FOR CALCULATING COMPLEX IMPEDENCE.

    for (int i = 0; i < index; i++) {
      if ((value[0][i] == 2)) {
        impedence(0, i) = {
            0, (2 * pie * freq[g] * value[4][i])};  // FOR INDUTANCE.
      }

      if ((value[0][i] == 1)) {
        impedence(0, i) = {
            0, (1 / (2 * pie * freq[g] * value[4][i]))};  // FOR CAPACITANCE
      }

      if ((value[0][i] == 0)) {
        impedence(0, i) = {value[4][i], 0};  // FOR RESISTANCE
      }

      if ((value[0][i] == 3) || (value[0][i]) == 4) {
        impedence(0, i) = {0, 0};  // FOR VOLTAGE AND CURRENT SOURCES.
      }
    }
    int rv = size - 1;
    for (int i = 0; i < index; i++) {
      if ((value[0][i] == 2) || (value[0][i] == 1) || (value[0][i] == 0))
        answer(1, i) =
            (answer(0, i) /
             impedence(
                 0, i));  // CURRENT = VOLTAGE/REACTANCE IS DEPICTED OVER HERE.

      if ((value[0][i] == 3)) {
        answer(1, i) = {(-1 * real(Result(rv, 0))), (-1 * imag(Result(rv, 0)))};
        rv++;  // CURRENT THROUGH VOLTAGE SOURCES.
      }
      if ((value[0][i] == 4))
        answer(1, i) = {value[6][i], 0};  // CURRENT OF CURRENT SOURCES.
    }

    double finalresult[4][index];  // FOR CONTAINING MAGNITUDE AND ARGUMENTS OF
                                   // ELEMENTS.
    for (int i = 0; i < index; i++) {
      finalresult[0][i] = abs(answer(
          0, i));  // MAGNITUDE CALCULATION OF COMPLEX MATRIX FOR VOLTAGES.
      finalresult[2][i] = abs(answer(
          1, i));  // MAGNITUDE CALCULATION OF COMPLEX MATRIX FOR CURRENTS.
    }

    for (int i = 0; i < index; i++) {
      finalresult[1][i] =
          ((arg(answer(0, i))) * 180) /
          (pie);  // ARGUMENT CALCULATION OF COMPLEX MATRIX FOR VOLTAGES.
      finalresult[3][i] =
          ((arg(answer(1, i))) * 180) /
          (pie);  // ARGUMENT CALCULATION OF COMPLEX MATRIX FOR VOLTAGES.
    }

    // CONVERTING THE RESULTS INTO STRING FOR WRITING IT IN THE RESULTZ.TXT FILE
    s = s + "\nFREQ = " + (to_string(freq[g] / 1000)) + "Khz\n";
    s = s + "\nVOLTAGES \n";
    for (int i = 0; i < index; i++) {
      s = s + data[0][i] + " " + (to_string(finalresult[0][i])) + " " +
          (to_string(finalresult[1][i])) + "\n";
    }
    s = s + "\nCURRENTS\n";
    for (int i = 0; i < index; i++) {
      s = s + data[0][i] + " " + (to_string(finalresult[2][i])) + " " +
          (to_string(finalresult[3][i])) + "\n";
    }
  }

  return s;
}

///////////////////////////////////////////////////////////////////////////////
//                END OF SOLVE CIRCUIT                                       //
///////////////////////////////////////////////////////////////////////////////