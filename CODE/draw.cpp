/////////////////////////////////////////////////////////////////////////////
//          DEFINITION OF FUNCTIONS OF DRAW.CPP
////
/////////////////////////////////////////////////////////////////////////////

//////////////////////////////
// INBUILT HEADERS REQUIRED //
//////////////////////////////
#include <iostream>
#include <regex>
#include <fstream>
#include <string.h>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <unordered_map>
#include <sstream>

//////////////////////
// HEADERS INCLUDED //
//////////////////////
#include <math.h>
#include "main.h"
#include "draw.h"
using namespace std;

/*
NOTE THAT IN ALL THE  FUNCTIONS OF DRAW.CPP  HAS A COMMON ARGUMENT i.e. "ofile "
WHICH IS
OF STRING TYPE , THIS STRING WILL CONTAIN ALL THE SVG CODE FOR DRAWING THE
CIRCUIT AND IT WILL BE FINALLY
RETURNED TO THE MAIN FUNCTION WHICH WILL WRITE IT INTO THE INTO INDIA.SVG FILE
THROUGH OFILE HANDLER WHICH
A VARIABLE OF OFSTREAM.
*/
///////////////////////////////////////////////////
//        INITIALIZE FUNCTION              //
///////////////////////////////////////////////////
/*
--------------  DESCRIPTION ABOUT IT :---------

=====)> THESE ARGUMENTS X-(WIDTH), Y-(HEIGHT), OFILE-(STRING)(COMMENTED ABOVE
ABOUT IT)
=====)> X - ACCORDING TO OUR LOGIC , WE WILL DETERMINE THE WIDTH OF THE SVG WITH
THE HELP OF TOTAL NETS PROVIDED TO
        US IN INPUT FILE. SINCE AFTER EACH ITERATION EACH ELEMENT WE ARE
SHIFTING THE X COORDINATE BY 100 UNITS , SO THE WIDTH WHICH
        WE ARE CALCULATING IS ((100*TOTAL INSTRUCTIONS)+200) AND THIS IS WHAT IS
COMING IN THE X ARGUMENT. SO THIS WILL BE OUR WIDTH
        OF THE SVG FILE.
=====)> Y - ACCORDING TO OUR LOGIC , WE WILL DETERMINE THE HEIGHT OF THE SVG
WITH THE HELP OF TOTAL NETS PROVIDED TO
        US IN INPUT FILE. SINCE AFTER EACH ITERATION EACH ELEMENT WE ARE
SHIFTING THE X COORDINATE BY 70 UNITS , SO THE HEIGHT WHICH
        WE ARE CALCULATING IS ((70 * TOTAL INSTRUCTIONS)+200) AND THIS IS WHAT
IS COMING IN THE X ARGUMENT. SO THIS WILL BE OUR HEIGHT
        OF THE SVG FILE.
*/
string initialize(int x, int y, string ofile) {
  string s1 = to_string(x);
  string s2 = to_string(y);
  ofile = ofile + "<svg width=\"" + s1 + "\" height=\"" + s2 + "\">\n";
  return ofile;
}
///////////////////////////////////////////////////
//        LINE FUNCTION                          //
///////////////////////////////////////////////////
/*
--------------  DESCRIPTION ABOUT IT :---------

=====)> X1 - }
=====)> Y1 - } }
                 } THESE FUNCTION ACCEPTS TO COORDINATES WHICH SAYS FROM WHERE
TO WE HAVE TO DRAW A LINE FROM X1,Y1 TO X2,Y2
=====)> X2 - } }
=====)> Y2 - }
=====)> OFILE - MENTIONED IN ABOVE COMMENTS (27-32)
*/
string line(int x1, int y1, int x2, int y2, string ofile) {
  string s1 = to_string(x1);
  string s2 = to_string(y1);
  string s3 = to_string(x2);
  string s4 = to_string(y2);
  ofile = ofile +
          "<line \
              transform=\"translate(25,5)\" \
              x1=\"" +
          s1 + "\" x2=\"" + s3 + "\" y1=\"" + s2 + "\" y2=\"" + s4 +
          "\" stroke-width=\"2.5\" stroke=\"black\"/> \n";

  return ofile;
}
///////////////////////////////////////////////////
//        RESISTOR FUNCTION                      //
///////////////////////////////////////////////////
/*
--------------  DESCRIPTION ABOUT IT :---------

=====)> X1 - )
              } THESE COORDINATE WILL DISPLACE RESITOR FROM 0,0 TO X,Y
COORDINATE IN SVG FILE
=====)> Y1 - )
=====)> OFILE - MENTIONED IN ABOVE COMMENTS (27-32)

*/
string resistor(int x1, int y1, string ofile) {
  string s1 = to_string(x1);
  string s2 = to_string(y1);
  ofile = ofile +
          "<path \
          transform=\"translate(" +
          s1 + "," + s2 +
          ") rotate(90 10 15)\" \
          d=\"M0 0 \
          l20 0  \
          l2.5 -10 \
          l5 20 \
          l5 -20 \
          l5 20  \
          l5 -20 \
          l5 20  \
          l2.5 -10 \
          l20 0\" stroke=\"black\" stroke-width=\"2.5\" stroke-linejoin=\"bevel\" fill=\"none\"> \
          </path> \n";
  return ofile;
}
///////////////////////////////////////////////////
//        CAPACITOR FUNCTION                     //
///////////////////////////////////////////////////
/*
--------------  DESCRIPTION ABOUT IT :---------
=====)> X1 - )
              } THESE COORDINATE WILL DISPLACE RESITOR FROM 0,0 TO X,Y
COORDINATE IN SVG FILE
=====)> Y1 - )
=====)> OFILE - MENTIONED IN ABOVE COMMENTS (27-32)
*/
string capacitor(int x1, int y1, string ofile) {
  string s1 = to_string(x1);
  string s2 = to_string(y1);
  ofile = ofile +
          "<path \
              transform=\"translate(" +
          s1 + "," + s2 +
          ") rotate(90 10 15)\" \
              d=\"M0 0  \
              l30 0  \
              l0 -20  \
              l0 40  \
              M40 0  \
              l0 -20  \
              l0 40   \
              l0 -20  \
              l30 0\" stroke=\"black\" stroke-width=\"2.5\" stroke-linejoin=\"bevel\" fill=\"none\"> \
               </path>\n";
  ofile = ofile +
          "<circle \
                    transform=\"translate(" +
          s1 + "," + s2 +
          ")\" \
                   cx=\"15\" cy=\"25\" r=\"2\" stroke=\"black\" stroke-width=\"2.5\" fill=\"black\"/> \n";

  return ofile;
}
///////////////////////////////////////////////////
//        INDUCTOR FUNCTION                      //
///////////////////////////////////////////////////
/*
--------------  DESCRIPTION ABOUT IT :---------

=====)> X1 - )
              } THESE COORDINATE WILL DISPLACE RESITOR FROM 0,0 TO X,Y
COORDINATE IN SVG FILE
=====)> Y1 - )
=====)> OFILE - MENTIONED IN ABOVE COMMENTS (27-32)
*/
string inductor(int x1, int y1, string ofile) {
  string s1 = to_string(x1);
  string s2 = to_string(y1);
  ofile = ofile +
          "<path \
              transform=\"translate(" +
          s1 + "," + s2 +
          ") rotate(90 10 15)\" \
               d=\" \
      M 0,0 \
      L 20.5,0 \
      C 20.5,0 20.5,-4 24.5,-4 \
      C 28.5,-4 28.5,0 28.5,0 \
      C 28.5,0 28.5,-4 32.5,-4 \
      C 36.5,-4 36.5,0 36.5,0 \
      C 36.5,0 36.5,-4 40.5,-4 \
      C 44.5,-4 44.5,0 44.5,0 \
      C 44.5,0 44.5,-4 48.5,-4 \
      C 52.5,-4 52.5,0 52.5,0 \
      L 70,0 \
    \" \
     stroke=\"black\" stroke-width=\"2.5\" stroke-linejoin=\"bevel\" fill=\"none\"> \
               </path>\n";
  return ofile;
}
///////////////////////////////////////////////////
//        DOT FUNCTION                            //
///////////////////////////////////////////////////
/*
--------------  DESCRIPTION ABOUT IT :---------

=====)> X1 - )
              } THESE COORDINATE WILL DISPLACE DOT FROM 0,0 TO X,Y COORDINATE IN
SVG FILE THIS DOT IS PLACED BECAUSE TO DETERMINE THE AMBIGUITY TO WHICH THE
TERMINAL IS CONNECTED
=====)> Y1 - )
=====)> OFILE - MENTIONED IN ABOVE COMMENTS (27-32)
*/
string dot(int x1, int y1, string ofile) {
  string s1 = to_string(x1);
  string s2 = to_string(y1);
  ofile = ofile +
          "<circle \
                    transform=\"translate(" +
          s1 + "," + s2 +
          ")\" \
                   cx=\"25\" cy=\"5\" r=\"2\" stroke=\"black\" stroke-width=\"2.5\" fill=\"black\"/> \n";
  return ofile;
}
///////////////////////////////////////////////////
//        AC SOURCE FUNCTION                     //
///////////////////////////////////////////////////
/*
--------------  DESCRIPTION ABOUT IT :---------

=====)> X1 - )
              } THESE COORDINATE WILL DISPLACE RESITOR FROM 0,0 TO X,Y
COORDINATE IN SVG FILE
=====)> Y1 - )
=====)> OFILE - MENTIONED IN ABOVE COMMENTS (27-32)
*/
string ac_source(int x1, int y1, string ofile) {
  string s1 = to_string(x1);
  string s2 = to_string(y1);
  ofile = ofile +
          "<line \
                 transform=\"translate(" +
          s1 + "," + s2 +
          ")\" \
                x1=\"25\" x2=\"25\" y1=\"5\" y2=\"20\" stroke-width=\"2.5\" stroke=\"black\"/> \n";
  ofile = ofile +
          "<line \
                 transform=\"translate(" +
          s1 + "," + s2 +
          ")\" \
                x1=\"10\" x2=\"10\" y1=\"15\" y2=\"20\" stroke-width=\"1.5\" stroke=\"black\"/> \n";
  ofile = ofile +
          "<line \
                 transform=\"translate(" +
          s1 + "," + s2 +
          ")\" \
                x1=\"7.5\" x2=\"12.5\" y1=\"17.5\" y2=\"17.5\" stroke-width=\"1.5\" stroke=\"black\"/> \n";

  ofile = ofile +
          "<circle \
                    transform=\"translate(" +
          s1 + "," + s2 +
          ")\" \
                   cx=\"25\" cy=\"40\" r=\"20\" stroke=\"black\" stroke-width=\"2.5\" fill=\"none\"/> \n";
  ofile = ofile +
          "<line \
                 transform=\"translate(" +
          s1 + "," + s2 +
          ")\" \
                x1=\"25\" x2=\"15\" y1=\"50\" y2=\"30\" stroke-width=\"2.5\" stroke=\"black\"/> \n";
  ofile = ofile +
          "<line \
                 transform=\"translate(" +
          s1 + "," + s2 +
          ")\" \
                x1=\"25\" x2=\"35\" y1=\"50\" y2=\"30\" stroke-width=\"2.5\" stroke=\"black\"/> \n";
  ofile = ofile +
          "<line \
                 transform=\"translate(" +
          s1 + "," + s2 +
          ")\" \
               x1=\"7.5\" x2=\"12.5\" y1=\"60\" y2=\"60\" stroke-width=\"1.5\" stroke=\"black\"/> \n";

  ofile = ofile +
          "<line \
                 transform=\"translate(" +
          s1 + "," + s2 +
          ")\" \
                x1=\"25\" x2=\"25\" y1=\"60\" y2=\"75\" stroke-width=\"2.5\" stroke=\"black\"/> \n";
  return ofile;
}
///////////////////////////////////////////////////
//      AC_CURRENT_SOURCE FUNCTION               //
///////////////////////////////////////////////////
/*
--------------  DESCRIPTION ABOUT IT :---------

=====)> X1 - )
              } THESE COORDINATE WILL DISPLACE RESITOR FROM (0,0) TO (X,Y)
COORDINATE IN SVG FILE
=====)> Y1 - )
=====)> OFILE - MENTIONED IN ABOVE COMMENTS (27-32)
*/
string ac_current(int x1, int y1, string ofile) {
  string s1 = to_string(x1);
  string s2 = to_string(y1);
  ofile = ofile +
          "<line \
                 transform=\"translate(" +
          s1 + "," + s2 +
          ")\" \
                x1=\"25\" x2=\"25\" y1=\"5\" y2=\"20\" stroke-width=\"2.5\" stroke=\"black\"/> \n";
  ofile = ofile +
          "<line \
                 transform=\"translate(" +
          s1 + "," + s2 +
          ")\" \
                x1=\"10\" x2=\"10\" y1=\"15\" y2=\"20\" stroke-width=\"1.5\" stroke=\"black\"/> \n";
  ofile = ofile +
          "<line \
                 transform=\"translate(" +
          s1 + "," + s2 +
          ")\" \
                x1=\"7.5\" x2=\"12.5\" y1=\"17.5\" y2=\"17.5\" stroke-width=\"1.5\" stroke=\"black\"/> \n";

  ofile = ofile +
          "<circle \
                    transform=\"translate(" +
          s1 + "," + s2 +
          ")\" \
                   cx=\"25\" cy=\"40\" r=\"20\" stroke=\"black\" stroke-width=\"2.5\" fill=\"none\"/> \n";
  ofile = ofile +
          "<line \
                 transform=\"translate(" +
          s1 + "," + s2 +
          ")\" \
                x1=\"25\" x2=\"25\" y1=\"25\" y2=\"55\" stroke-width=\"2.5\" stroke=\"black\"/> \n";
  ofile = ofile +
          "<line \
                 transform=\"translate(" +
          s1 + "," + s2 +
          ")\" \
                x1=\"25\" x2=\"15\" y1=\"25\" y2=\"35\" stroke-width=\"2.5\" stroke=\"black\"/> \n";
  ofile = ofile +
          "<line \
                 transform=\"translate(" +
          s1 + "," + s2 +
          ")\" \
                x1=\"25\" x2=\"35\" y1=\"25\" y2=\"35\" stroke-width=\"2.5\" stroke=\"black\"/> \n";
  ofile = ofile +
          "<line \
                 transform=\"translate(" +
          s1 + "," + s2 +
          ")\" \
               x1=\"7.5\" x2=\"12.5\" y1=\"60\" y2=\"60\" stroke-width=\"1.5\" stroke=\"black\"/> \n";

  ofile = ofile +
          "<line \
                 transform=\"translate(" +
          s1 + "," + s2 +
          ")\" \
                x1=\"25\" x2=\"25\" y1=\"60\" y2=\"75\" stroke-width=\"2.5\" stroke=\"black\"/> \n";
  return ofile;
}
///////////////////////////////////////////////////
//        EARTHING  FUNCTION                     //
///////////////////////////////////////////////////
/*
--------------  DESCRIPTION ABOUT IT :---------

=====)> X1 - )
              } THESE COORDINATE WILL DISPLACE RESITOR FROM 0,0 TO X,Y
COORDINATE IN SVG FILE
=====)> Y1 - )
=====)> OFILE - MENTIONED IN ABOVE COMMENTS (27-32)
*/
string earthing(int x1, int y1, string ofile) {
  string s1 = to_string(x1);
  string s2 = to_string(y1);
  ofile = ofile +
          "<path \
              transform=\"translate(" +
          s1 + "," + s2 +
          ") rotate(90 10 15)\" \
              d=\"M0 0  \
              l20 0  \
              l0 -20  \
              l0 40  \
              M15 0  \
              l0 -30  \
              l0 60   \
              l0 -30  \
              l10 0M25 0 l0 -10 l0 20 \
              \" stroke=\"black\" stroke-width=\"2.5\" stroke-linejoin=\"bevel\" fill=\"none\"> \
               </path>\n";

  return ofile;
}
///////////////////////////////////////////////////
//        TEXT  FUNCTION                         //
///////////////////////////////////////////////////
/*
--------------  DESCRIPTION ABOUT IT :---------

=====)> X - )
              }  THESE COORDINATE WILL DISPLACE RESITOR FROM 0,0 TO X,Y
COORDINATE IN SVG FILE
=====)> Y - )
=====)> S - THIS IS THE TEXT WHICH WE NEED TO DISPLACE
=====)> OFILE - MENTIONED IN ABOVE COMMENTS (27-32)
*/
string text(int x, int y, string s, string ofile) {
  string s1 = to_string(x);
  string s2 = to_string(y);
  ofile = ofile +
          "<text \
            x = \"" +
          s1 + "\" y=\"" + s2 +
          "\" stroke-width=\"5.0\" font-size=\"10\" \
                style=\"writing-mode: tb;\" \
                fill=\"black\">" +
          s + "</text>\n";
  return ofile;
}
// string text_position(int x, int y, int displace, string ofile)
// {
//   return ofile;
// }
///////////////////////////////////////////////////
//        END FUNCTION                           //
///////////////////////////////////////////////////
/*
--------------  DESCRIPTION ABOUT IT :---------
=====)> OFILE - MENTIONED IN ABOVE COMMENTS (27-32)
*/
string end(string ofile) {
  ofile = ofile + "</svg>";
  return ofile;
}
///////////////////////////////////////////////////
//        DRAW_INSTRUCTION FUNCTION              //
///////////////////////////////////////////////////
/*
--------------  DESCRIPTION ABOUT IT :---------
=====)> THIS IS THE MAIN FUNCTION OF DRAW WHICH
        CALLS THE ABOVE FUNCTIONS WHENEVER REQUIRED.
        IT MAKES A MATRIX OF NxM CONTAINING 0 AND 1
        WHERE N DENOTES NO. OF DISTINCT NETS AND M
        DENOTES TO NO. OF INSTRUCTION IN INPUT FILE.

WE ARE BASICALLY CREATING A SPACE OF (100*M+220)x(70*N+200) IN SVG FILE
SINCE 70 IS THE WIDTH OF OUR ELEMENT. AND 100 BECAUSE AFTER EACH ITERATION
WE ARE MOVING THE X COORDINATE BY 100.
THE MATRIX DESCRIBED ABOVE CONTAINS 2 1s IN EACH COLUMN SINCE EACH ELEMENT
HAS TWO TERMINALS AND THESE MATRIX DENOTES ITS CONNECTION WITH DIFFENT NETS.
  IN ORDER TO REMOVE CUTTING WIRES WE HAVE SORTED THE MATRIX BY CONSIDERING THE
DIFFERENCE
OF ITS NETS. HOWEVER , THERE ARE STILL POSSIBITLITY OF CUTTINGS.
SO, WE HAVE MADE A DOT FUNCTION ABOVE TO DETERMINE THE EXACT NETS TO WHICH IT IS
CONNECTED.
*/

string draw_instruction(vector<double> value[], vector<string> data[],
                        int index) {
  // cout<<"my name is rahul\n";
  int x[(2 * index)];

  for (int i = 0; i < index; i++) {
    x[i] = (int)(value[2][i]);
  }
  int j = index;
  for (int i = 0; i < index; i++) {
    x[j] = (int)(value[3][i]);
    j++;
  }
  sort(x, x + (2 * index));

  for (int i = 0; i < (2 * index - 1); i++) {
    if (x[i + 1] == x[i]) x[i] = 10007;
  }
  sort(x, x + (2 * index));

  int size = 0, flag = 0;
  for (int i = 0; i < (2 * index); i++) {
    // cout<<x[i]<<" ";
    if ((x[i] == 10007) && (flag == 0)) {
      size = i;
      flag = 1;
    }
  }

  int terminals[size + 2][index + 1];
  for (int i = 0; i < size + 2; i++) {
    for (int j = 0; j < index + 1; j++) {
      terminals[i][j] = 0;
    }
  }

  for (int j = 1; j < index + 1; j++) {
    terminals[0][j] = value[0][j - 1];
    terminals[1][j] = value[1][j - 1];
  }

  for (int i = 2; i < size + 2; i++) {
    terminals[i][0] = x[size + 1 - i];
  }
  // for(int i=0;i<(2*index);i++)
  // {
  //   cout<<x[i]<<" ";
  // }
  // cout<<endl;
  for (int j = 1; j < index + 1; j++) {
    int x = value[2][j - 1];
    for (int i = 2; i < size + 2; i++) {
      if (x == terminals[i][0]) terminals[i][j] += 1;
    }
    x = value[3][j - 1];
    for (int i = 2; i < size + 2; i++) {
      if (x == terminals[i][0]) terminals[i][j] += 1;
    }
  }
  int diff[index + 1];
  for (int i = 1; i < index + 1; i++) {
    int diff1, diff2, flag1 = 0, flag2 = 0;
    for (int j = 2; j < size + 2; j++) {
      if ((terminals[j][i] == 1) && (flag1 == 0)) {
        diff1 = j;
        flag1 = 1;
      } else if ((terminals[j][i] == 1) && (flag2 == 0)) {
        diff2 = j;
        flag2 = 1;
      }
    }
    diff[i] = abs(diff2 - diff1);
  }
  unordered_map<string, int> wordMap;
  for (int i = 0; i < index; i++) {
    wordMap.insert({data[0][i], diff[i + 1]});
  }
  sort(diff + 1, diff + index + 1, greater<int>());
  int f = 1;
  int result[size + 2][index + 1], arr[size + 2][index + 1];

  for (int i = 0; i < size + 2; i++) {
    for (int j = 0; j < index + 1; j++) {
      arr[i][j] = 0;
    }
  }

  for (int i = 1; i < index + 1; i++) {
    int retain = diff[i];
    for (std::pair<string, int> element : wordMap) {
      if (element.second == retain) {
        for (int k = 1; k < index + 1; k++) {
          if (diff[k] == retain) diff[k] = 0;
        }
        for (int k = 0; k < index; k++) {
          if (data[0][k] == element.first) {
            for (int t = 0; t < size + 2; t++) {
              result[t][f] = terminals[t][k + 1];
            }
            f++;
          }
        }
      }
    }
  }
  result[0][0] = 0;
  result[1][0] = 0;
  for (int i = 2; i < size + 2; i++) {
    result[i][0] = x[size + 1 - i];
  }

  //   for (std::pair<string,int> element : wordMap)
  //   cout << element.first << " :: " << element.second << std::endl;
  // // for(int i=0;i<index+1;i++)
  //   cout<<diff[i]<<" ";
  // cout<<endl;
  int yr = (size + 1) * 70 + 200;
  int xr = index * 100 + 200;
  int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
  string s = "";
  s = initialize(xr, yr, s);
  // s = dot(0,0,s);
  // s = resistor(0,0,s);
  for (int j = 1; j < index + 1; j++) {
    int flagr1 = 0, flagr2 = 0, flagc1 = 0, flagc2 = 0, flagl1 = 0, flagl2 = 0,
        flagi1 = 0, flagi2 = 0, flagv1 = 0, flagv2 = 0;
    x1 = x1 + 100;
    x2 = x2 + 100;
    y1 = 30;
    y2 = 30;
    if (result[0][j] == 0) {
      string m = "R";
      string n = to_string(result[1][j]);
      string val;
      m = m + n;
      for (int o = 0; o < index; ++o) {
        if (data[0][o] == m) val = data[3][o];
      }
      for (int i = 2; i < size + 2; i++) {
        if (flagr1 == 0) {
          y1 += 70;
        }
        if (flagr2 == 0) {
          y2 += 70;
        }
        if ((result[i][j] == 1) && (flagr1 == 0)) {
          s = text(x1 + 50, y1 + 25, m + "=", s);
          s = text(x1 + 50, y1 + 45, val, s);
          s = resistor(x1, y1, s);
          s = dot(x1, y1, s);
          flagr1 = 1;
          arr[i][j] = x1;
        } else if ((result[i][j] == 1) && (flagr2 == 0)) {
          s = line(x1, y1 + 70, x2, y2, s);
          s = dot(x2, y2, s);
          flagr2 = 1;
          arr[i][j] = x2;
        }
      }
    }
    if (result[0][j] == 1) {
      string m = "C";
      string n = to_string(result[1][j]);
      string val;
      m = m + n;
      for (int o = 0; o < index; ++o) {
        if (data[0][o] == m) val = data[3][o];
      }
      for (int i = 2; i < size + 2; i++) {
        if (flagc1 == 0) {
          y1 += 70;
        }
        if (flagc2 == 0) {
          y2 += 70;
        }
        if ((result[i][j] == 1) && (flagc1 == 0)) {
          s = text(x1 + 70, y1 + 15, m + "=", s);
          s = text(x1 + 70, y1 + 35, val, s);
          s = capacitor(x1, y1, s);
          s = dot(x1, y1, s);
          flagc1 = 1;
          arr[i][j] = x1;
        } else if ((result[i][j] == 1) && (flagc2 == 0)) {
          s = line(x1, y1 + 70, x2, y2, s);
          s = dot(x2, y2, s);
          flagc2 = 1;
          arr[i][j] = x2;
        }
      }
    }
    if (result[0][j] == 2) {
      string m = "L";
      string n = to_string(result[1][j]);
      string val;
      m = m + n;
      for (int o = 0; o < index; ++o) {
        if (data[0][o] == m) val = data[3][o];
      }
      for (int i = 2; i < size + 2; i++) {
        if (flagl1 == 0) {
          y1 += 70;
        }
        if (flagl2 == 0) {
          y2 += 70;
        }
        if ((result[i][j] == 1) && (flagl1 == 0)) {
          s = text(x1 + 50, y1 + 15, m + "=", s);
          s = text(x1 + 50, y1 + 35, val, s);
          s = inductor(x1, y1, s);
          s = dot(x1, y1, s);
          flagl1 = 1;
          arr[i][j] = x1;
        } else if ((result[i][j] == 1) && (flagl2 == 0)) {
          s = line(x1, y1 + 70, x2, y2, s);
          s = dot(x2, y2, s);
          flagl2 = 1;
          arr[i][j] = x2;
        }
      }
    }

    if (result[0][j] == 4) {
      string m = "I";
      string n = to_string(result[1][j]);
      string val1, val2, val3;
      m = m + n;
      for (int o = 0; o < index; ++o) {
        if (data[0][o] == m) {
          val1 = data[3][o] + " ";
          val2 = data[4][o] + " " + data[5][o] + " " + data[6][o] + " " +
                 data[7][o];
          val3 = data[8][o] + " " + data[9][o] + " " + data[10][o];
        }
      }
      for (int i = 2; i < size + 2; i++) {
        if (flagi1 == 0) {
          y1 += 70;
        }
        if (flagi2 == 0) {
          y2 += 70;
        }
        if ((result[i][j] == 1) && (flagi1 == 0)) {
          s = text(x1 + 75, y1 + 25, m + "=", s);
          s = text(x1 + 75, y1 + 45, val1, s);
          s = text(x1 + 65, y1 + 15, val2, s);
          s = text(x1 + 55, y1 + 25, val3, s);
          s = ac_current(x1, y1, s);
          s = dot(x1, y1, s);
          flagi1 = 1;
          arr[i][j] = x1;
        } else if ((result[i][j] == 1) && (flagi2 == 0)) {
          s = line(x1, y1 + 70, x2, y2, s);
          s = dot(x2, y2, s);
          flagi2 = 1;
          arr[i][j] = x2;
        }
      }
    }

    if (result[0][j] == 3) {
      string m = "V";
      string n = to_string(result[1][j]);
      string val1, val2, val3;
      m = m + n;
      for (int o = 0; o < index; ++o) {
        if (data[0][o] == m) {
          val1 = data[3][o] + " ";
          val2 = data[4][o] + " " + data[5][o] + " " + data[6][o] + " " +
                 data[7][o];
          val3 = data[8][o] + " " + data[9][o] + " " + data[10][o];
        }
      }

      for (int i = 2; i < size + 2; i++) {
        if (flagv1 == 0) {
          y1 += 70;
        }
        if (flagv2 == 0) {
          y2 += 70;
        }
        if ((result[i][j] == 1) && (flagv1 == 0)) {
          s = text(x1 + 75, y1 + 25, m + "=", s);
          s = text(x1 + 75, y1 + 45, val1, s);
          s = text(x1 + 65, y1 + 15, val2, s);
          s = text(x1 + 55, y1 + 25, val3, s);
          s = ac_source(x1, y1, s);
          s = dot(x1, y1, s);
          flagv1 = 1;
          arr[i][j] = x1;
        } else if ((result[i][j] == 1) && (flagv2 == 0)) {
          s = line(x1, y1 + 70, x2, y2, s);
          s = dot(x2, y2, s);
          flagv2 = 1;
          arr[i][j] = x2;
        }
      }
    }
  }
  for (int i = 0; i < 2; i++) {
    for (int j = 1; j < index + 1; j++) {
      arr[i][j] = result[i][j];
    }
  }

  for (int i = 2; i < size + 2; i++) {
    arr[i][0] = result[i][0];
  }
  int x11 = 0, y11 = 30, x22 = 0, y22 = 30;
  for (int i = 2; i < size + 2; i++) {
    int flagt = 0, flagtt = 0;
    y11 = y11 + 70;
    y22 = y22 + 70;
    for (int j = 1; j < index + 1; j++) {
      if ((arr[i][j] != 0) && (flagt == 0)) {
        x11 = arr[i][j];
        flagt = 1;
      }
      if ((arr[i][index + 1 - j] != 0) && (flagtt == 0)) {
        x22 = arr[i][index + 1 - j];
        flagtt = 1;
      }
      if ((flagt == 1) && (flagtt == 1)) {
        if (arr[i][0] != -1)
          s = text(x11 + 70, y11 - 25, "NET" + (to_string(arr[i][0])), s);
        s = line(x11 - 1.0, y11 + 0.5, x22 + 1.0, y22 + 0.5, s);
        if (arr[i][0] == -1) {
          s = text(x11 + 35, y11 - 5, "O", s);
          s = earthing((x11 - 1.0 + x22 + 1.0) / 2, y11, s);
        }
      }
    }
  }

  s = end(s);

  //  for(int i=0;i<size+2;i++)
  //  {
  //    for(int j=0;j<index+1;j++)
  //    {
  //     cout<<result[i][j]<<" ";
  //    }
  //    cout<<endl;
  //  }
  // cout<<s;
  return s;
}
// int main()
// {
//   fstream ifile;
//   string s="";
//   ifile.open("india.svg",ios::out);
//   int x=3305,y=2290,z=90;
//   s=initialize(x,y,z,s);
//   s=resistor(50,50,s);
//   s=capacitor(10,10,s);
//    s=inductor(200,20,s);
//   s=line(100,0,100,100,s);
//   s=text(10,5,"R1 = 6K",s);
//   s=ac_current(300,300,s);
//   s=ac_source(70,100,s);
//  // s=earthing(0,0,s);
//   s=end(0,0,0,s);
//   cout<<s<<endl;
//   ifile<<s;
//   ifile.close();
// }

///////////////////////////////////////////////////
//        END OF THE DRAW CLASS                  //
///////////////////////////////////////////////////