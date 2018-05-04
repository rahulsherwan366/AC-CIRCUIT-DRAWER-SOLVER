//////////////////////////////////////////
//   INBUILT HEADERS REQUIRED			//
//////////////////////////////////////////
#include <iostream>
#include <regex>
#include <fstream>
#include <string.h>
#include <vector>
#include <stdlib.h>
#include <sstream>

//////////////////////////////////////////
//		HEADERS INCLUDED                //
//////////////////////////////////////////
#include "solve.h"
#include "main.h"
#include "draw.h"

using namespace std;

//////////////////////////////////////////
//			CALCULTE FUNCTION 			//
//////////////////////////////////////////
//--------------DISCRIPTION-------------//
// IT CONVERTS STRING INTO INTEGER USING//
// GEEK FUNCTION WHICH IS DIFINED IN    //
// SSTREAM HEADER FILE.                 //
//------------------END-----------------//
int calculate(string s) {
  stringstream geek(s);
  int x = 0;
  geek >> x;  // CONVERTS STRING STREAM INTO INTEGER.
  return x;
}

//////////////////////////////////////////
//			NUMBER   FUNCTION 			//
//////////////////////////////////////////
//--------------DISCRIPTION-------------//
// IT DETERMINES AND REMOVE ALPHABETS PART OF STRING
// AND RETURNS THE ONLY NUMBERS IN THE
// FORM OF STRING.
//------------------END-----------------//
string number(string s) {
  string t;
  t = s;
  s = "";
  for (int i = 0; i < t.size(); i++) {
    if ((t[i] <= '9') && (t[i] >= '0') || (t[i] == '.')) s += t[i];
  }
  return s;
}

/////////////////////////////
// 			MAIN FUNCTION  //
/////////////////////////////
// THIS FUNCTION READS THE INPUT FILE , PARSES IT AND CALLS THE DRAW AND SOLVE
// FUNCTION
// AND FINALLY WRITES THE DATA INTO TOP.SVG AND RESULTS.TXT WHATEVER DRAW AND
// SOLVE FUNCTION RETURNS
// RESPECTIVELY.
int main() {
  ifstream ifile;  // FOR INPUT FILE
  ofstream ofile;  // FOR OUTPUT FILE
  int index = 0;
  vector<string> data[11];   // FOR STORING INPUT FILE IN FORM OF STRING.
  vector<double> value[10];  // FOR STORING INPUT FILE IN FORM OF DOUBLE.
  string q, r, s, tt, u, v, w, x, y, z, zz, temp;  // TEMPORARY VARIABLES.
  ifile.open("top.cir", ios::in | ios::out);       // OPENING THE FILE.
  // regex
  // firstexp("((NET|R|C|L|V|I)[[:digit:]]+)|(SINE)|(([[:digit:]]+|[[:digit:]]+(.)[[:digit:]]+)(K|hz|UF|MF|NF|NH|UH|MH|Khz))");
  // regex
  // secondexp("(\\()|(\\))|([[:digit:]]+|[[:digit:]]+(.)[[:digit:]]+)|([[:digit:]]+|[[:digit:]]+(.)[[:digit:]]+S)");
  while (!ifile.eof())  // BREAKS WHEN END OF FILE IS REACHED.
  {  // READING DATA
    ifile >> q;
    ifile >> r;
    ifile >> s;
    ifile >> tt;
    if ((q[0] == 'V') || (q[0] == 'I')) {
      ifile >> u >> v >> w >> x >> y;
      ifile >> z;
      if (z != ")")
        ifile >> zz;
      else
        zz = "0";
    }
    // STORING THE READ DATA
    data[0].push_back(q);
    data[1].push_back(r);
    data[2].push_back(s);
    data[3].push_back(tt);
    if ((q[0] == 'V') || (q[0] == 'I')) {
      data[4].push_back(u);
      data[5].push_back(v);
      data[6].push_back(w);
      data[7].push_back(x);
      data[8].push_back(y);
      if (z != ")") {
        data[9].push_back(z);
        data[10].push_back(zz);
      } else {
        data[9].push_back(zz);
        data[10].push_back(z);
      }

    } else {
      data[4].push_back("0");
      data[5].push_back("0");
      data[6].push_back("0");
      data[7].push_back("0");
      data[8].push_back("0");
      data[9].push_back("0");
      data[10].push_back("0");
    }
    index++;
  }
  ifile.close();
  // DEFINING REGULAR EXPRESSION .
  regex firstexp("((R|C|L|V|I)[[:digit:]]+)");
  regex secondexp(
      "(NET[[:digit:]]+)|(Net[[:digit:]]+)|(net[[:digit:]]+)|([[:digit:]]+)");
  regex thirdexp(
      "(NET[[:digit:]]+)|(Net[[:digit:]]+)|(net[[:digit:]]+)|([[:digit:]]+)");
  regex fourthexp(
      "((([[:digit:]]+)|([[:digit:]]+(.)[[:digit:]]+))(|K|M|U|N|MF|UF|F|NF|H|"
      "MH|UH|NH))|(sine)|(Sine)|(SINE)");
  regex fifthexp("0|(\\()");
  regex sixthexp("0|([[:digit:]]+|[[:digit:]]+(.)[[:digit:]]+)");
  regex seventhexp("0|([[:digit:]]+|[[:digit:]]+(.)[[:digit:]]+)");
  regex eightexp(
      "0|(([[:digit:]]+|[[:digit:]]+(.)[[:digit:]]+)(hz|Khz|Mhz|Ghz))");
  regex ninethexp(
      "0|(([[:digit:]]+|[[:digit:]]+(.)[[:digit:]]+)(KS|S|US|MS|NS))");
  regex tenthexp("0|([[:digit:]]+|[[:digit:]]+(.)[[:digit:]]+)");
  regex eleventhexp("0|(\\))");
  int flag[11];
  for (int j = 0; j < 11; j++) {
    flag[j] = 0;
  }
  // cout<<data[3][0]<<endl;

  // CHECKING WHETHER THE TOKENS ARE VALID OR NOT
  for (int i = 0; i < index; i++) {  // cout<<data[j][i]<<" ";
    if (regex_match(data[0][i], firstexp)) {  // cout<<"valid"<<endl;
      // cout<<data[0][i]<<endl;
      flag[0] = 1;
    }
    if (regex_match(data[1][i], secondexp)) {  // cout<<"valid"<<endl;
      // cout<<data[1][i]<<endl;
      flag[1] = 1;
    }
    if (regex_match(data[2][i], thirdexp)) {  // cout<<"valid"<<endl;
      // cout<<data[2][i]<<endl;
      flag[2] = 1;
    }
    if (regex_match(data[3][i], fourthexp)) {  // cout<<"valid"<<endl;
      // cout<<data[3][i]<<endl;
      flag[3] = 1;
    }
    if (regex_match(data[4][i], fifthexp)) {  // cout<<"valid"<<endl;
      // cout<<data[4][i]<<endl;
      flag[4] = 1;
    }
    if (regex_match(data[5][i], sixthexp)) {  // cout<<"valid"<<endl;
      // cout<<data[5][i]<<endl;
      flag[5] = 1;
    }
    if (regex_match(data[6][i], seventhexp)) {  // cout<<"valid"<<endl;
      // cout<<data[6][i]<<endl;
      flag[6] = 1;
    }
    if (regex_match(data[7][i], eightexp)) {  // cout<<"valid"<<endl;
      // cout<<data[7][i]<<endl;
      flag[7] = 1;
    }
    if (regex_match(data[8][i], ninethexp)) {  // cout<<"valid"<<endl;
      // cout<<data[8][i]<<endl;
      flag[8] = 1;
    }
    if (regex_match(data[9][i], tenthexp)) {  // cout<<"valid"<<endl;
      // cout<<data[9][i]<<endl;
      flag[9] = 1;
    }
    if (regex_match(data[10][i], eleventhexp)) {  // cout<<"valid"<<endl;
      // cout<<data[10][i]<<endl;
      flag[10] = 1;
    }

    // IF NOT VALID THEN REPORTING ERRORS.
    if (flag[0] == 1)
      flag[0] = 0;
    else {
      cout << "error in line " << i + 1 << endl;
      exit(0);
    }
    if (flag[1] == 1)
      flag[1] = 0;
    else {
      cout << "error in line " << i + 1 << endl;
      exit(0);
    }
    if (flag[2] == 1)
      flag[2] = 0;
    else {
      cout << "error in line " << i + 1 << endl;
      exit(0);
    }
    if (flag[3] == 1)
      flag[3] = 0;
    else {
      cout << "error in line " << i + 1 << endl;
      exit(0);
    }
    if (flag[4] == 1)
      flag[4] = 0;
    else {
      cout << "error in line " << i + 1 << endl;
      exit(0);
    }
    if (flag[5] == 1)
      flag[5] = 0;
    else {
      cout << "error in line " << i + 1 << endl;
      exit(0);
    }
    if (flag[6] == 1)
      flag[6] = 0;
    else {
      cout << "error in line " << i + 1 << endl;
      exit(0);
    }
    if (flag[7] == 1)
      flag[7] = 0;
    else {
      cout << "error in line " << i + 1 << endl;
      exit(0);
    }
    if (flag[8] == 1)
      flag[8] = 0;
    else {
      cout << "error in line " << i + 1 << endl;
      exit(0);
    }
    if (flag[9] == 1)
      flag[9] = 0;
    else {
      cout << "error in line " << i + 1 << endl;
      exit(0);
    }
    if (flag[10] == 1)
      flag[10] = 0;
    else {
      cout << "error in line " << i + 1 << endl;
      exit(0);
    }
  }
  // for(int j=0;j<11;j++)
  // {
  // 	for(int i=0;i<index;i++)
  // 	{
  // 		cout<<data[j][i]<<" ";
  // 	}
  // 	cout<<endl;
  // }
  string t;
  // AFTER CHECKING VALIDITY OF TOKENS NOW, BELOW , WE ARE CHECKING
  // WHETHER IT IS IN THE RIGHT SEQUENCE OR NOT.
  for (int i = 0; i < index; i++) {
    if (data[0][i][0] == 'R') {
      value[0].push_back(0);
      t = data[0][i].substr(1);
      value[1].push_back(calculate(t));
    } else if (data[0][i][0] == 'C') {
      value[0].push_back(1);
      t = data[0][i].substr(1);
      value[1].push_back(calculate(t));
    } else if (data[0][i][0] == 'L') {
      value[0].push_back(2);
      t = data[0][i].substr(1);
      value[1].push_back(calculate(t));
    } else if (data[0][i][0] == 'V') {
      value[0].push_back(3);
      t = data[0][i].substr(1);
      value[1].push_back(calculate(t));
    } else if (data[0][i][0] == 'I') {
      value[0].push_back(4);
      t = data[0][i].substr(1);
      value[1].push_back(calculate(t));
    } else
      continue;
    if (data[1][i][0] == 'N') {
      t = data[1][i].substr(3);
      // cout<<t<<" "<<data[1][i][0];
      value[2].push_back(calculate(t));
    } else if (data[1][i][0] != 'N')
      value[2].push_back(-1);
    else
      continue;

    if (data[2][i][0] == 'N') {
      t = data[2][i].substr(3);
      value[3].push_back(calculate(t));
    } else if (data[2][i][0] != 'N')
      value[3].push_back(-1);
    else
      continue;

    // IF THEY ARE IN RIGHT SEQUENCE THEN IT IS DECODED OF INTO INTEGER.
    if (data[3][i][0] == 'S')
      value[4].push_back(-77);
    else if ((data[3][i][0] <= '9') && (data[3][i][0] >= '0')) {
      t = data[3][i];
      string p = data[3][i];
      float result;
      // cout<<t<<" sdf"<<endl;
      t = number(t);
      bool found = false;
      for (int r = 0; r < t.size(); r++) {
        if (t[r] == '.') found = true;
      }
      int x = t.find(".");
      if (found == true) {
        string t1, t2;
        float y, z, u = 1, flag2 = 0;
        t1 = t.substr(0, x);
        t2 = t.substr(x + 1);
        cout << t2 << endl;
        if (t2[0] == '0') {
          for (int p = 0; p < t2.size(); p++) {
            if ((t2[p] == '0') && (flag2 == 0)) {
              u = u * 10;
              cout << u << endl;
              if (t2[p + 1] != '0') flag2 = 1;
            }
          }
        }
        y = (float)(calculate(t1));
        z = (float)(calculate(t2));
        if (z < 10.0)
          z = z / (10 * u);
        else if (z < 100.0)
          z = z / (100 * u);
        else if (z < 1000.0)
          z = z / (1000.0 * u);
        else
          z = z / (10000.0 * u);
        result = y + z;
        if (p[p.size() - 1] == 'K')
          result = result * 1000;
        else if (p[p.size() - 2] == 'N')
          result = ((double)(result)) / 1000000000;
        else if (p[p.size() - 2] == 'U')
          result = ((double)(result)) / 1000000;
        else if (p[p.size() - 2] == 'M')
          result = ((double)(result)) / 1000;
        else
          result = result;

      } else {  // cout<<p.size()-2<<endl;
        if (p[p.size() - 1] == 'K')
          result = calculate(t) * 1000;
        else if (p[p.size() - 2] == 'N')
          result = ((double)(calculate(t))) / 1000000000;
        else if (p[p.size() - 2] == 'U')
          result = ((double)(calculate(t))) / 1000000;
        else if (p[p.size() - 2] == 'M')
          result = ((double)(calculate(t))) / 1000;
        else
          result = calculate(t);
      }
      // cout<<t<<" sdf"<<endl;
      value[4].push_back(result);
    } else
      continue;

    if ((data[5][i][0] <= '9') && (data[5][i][0] >= '0')) {
      t = data[5][i];
      float result;
      // cout<<t<<" sdf"<<endl;
      t = number(t);
      bool found = false;
      for (int r = 0; r < t.size(); r++) {
        if (t[r] == '.') found = true;
      }
      int x = t.find(".");
      if (found == true) {
        string t1, t2;
        float y, z, u = 1, flag2 = 0;
        t1 = t.substr(0, x);
        t2 = t.substr(x + 1);
        if (t2[0] == '0') {
          for (int p = 0; p < t2.size(); p++) {
            if ((t2[p] == '0') && (flag2 == 0)) {
              u = u * 10;
              if (t2[p + 1] != '0') flag2 = 1;
            }
          }
        }
        y = (float)(calculate(t1));
        z = (float)(calculate(t2));
        if (z < 10.0)
          z = z / (10 * u);
        else if (z < 100.0)
          z = z / (100 * u);
        else if (z < 1000.0)
          z = z / (1000.0 * u);
        else
          z = z / (10000.0 * u);
        result = y + z;
      } else
        result = calculate(t);
      // cout<<t<<" sdf"<<endl;
      value[5].push_back(result);
    }

    if ((data[6][i][0] <= '9') && (data[6][i][0] >= '0')) {
      t = data[6][i];
      float result;
      // cout<<t<<" sdf"<<endl;
      t = number(t);
      bool found = false;
      for (int r = 0; r < t.size(); r++) {
        if (t[r] == '.') found = true;
      }
      int x = t.find(".");
      if (found == true) {
        string t1, t2;
        float y, z, u = 1, flag2 = 0;
        t1 = t.substr(0, x);
        t2 = t.substr(x + 1);
        if (t2[0] == '0') {
          for (int p = 0; p < t2.size(); p++) {
            if ((t2[p] == '0') && (flag2 == 0)) {
              u = u * 10;
              if (t2[p + 1] != '0') flag2 = 1;
            }
          }
        }
        y = (float)(calculate(t1));
        z = (float)(calculate(t2));
        if (z < 10.0)
          z = z / (10 * u);
        else if (z < 100.0)
          z = z / (100 * u);
        else if (z < 1000.0)
          z = z / (1000.0 * u);
        else
          z = z / (10000.0 * u);
        result = y + z;
      } else
        result = calculate(t);
      // cout<<t<<" sdf"<<endl;
      value[6].push_back(result);
    }

    if ((data[7][i][0] <= '9') && (data[7][i][0] >= '0')) {
      t = data[7][i];
      string p = data[7][i];
      float result;
      // cout<<t<<" sdf"<<endl;
      t = number(t);
      bool found = false;
      for (int r = 0; r < t.size(); r++) {
        if (t[r] == '.') found = true;
      }
      int x = t.find(".");
      if (found == true) {
        string t1, t2;
        float y, z, u = 1, flag2 = 0;
        t1 = t.substr(0, x);
        t2 = t.substr(x + 1);
        if (t2[0] == '0') {
          for (int p = 0; p < t2.size(); p++) {
            if ((t2[p] == '0') && (flag2 == 0)) {
              u = u * 10;
              if (t2[p + 1] != '0') flag2 = 1;
            }
          }
        }
        y = (float)(calculate(t1));
        z = (float)(calculate(t2));
        if (z < 10.0)
          z = z / (10 * u);
        else if (z < 100.0)
          z = z / (100 * u);
        else if (z < 1000.0)
          z = z / (1000.0 * u);
        else
          z = z / (10000.0 * u);
        result = y + z;
        if (p[p.size() - 3] == 'K')
          result = result * 1000;
        else if (p[p.size() - 3] == 'M')
          result = result * 1000000;
        else if (p[p.size() - 3] == 'G')
          result = result * 1000000000;
        else
          result = result;
      } else {  // cout<<p[p.size()-3]<<endl;
        if (p[p.size() - 3] == 'K')
          result = calculate(t) * 1000;
        else if (p[p.size() - 3] == 'M')
          result = calculate(t) * 1000000;
        else if (p[p.size() - 3] == 'G')
          result = calculate(t) * 1000000000;
        else
          result = calculate(t);
      }
      // cout<<t<<" sdf"<<endl;
      value[7].push_back(result);
    }

    if ((data[8][i][0] <= '9') && (data[8][i][0] >= '0')) {
      t = data[8][i];
      string p = data[8][i];
      float result;
      // cout<<t<<" sdf"<<endl;
      t = number(t);
      bool found = false;
      for (int r = 0; r < t.size(); r++) {
        if (t[r] == '.') found = true;
      }
      int x = t.find(".");
      if (found == true) {
        string t1, t2;
        float y, z, u = 1, flag2 = 0;
        t1 = t.substr(0, x);
        t2 = t.substr(x + 1);
        if (t2[0] == '0') {
          for (int p = 0; p < t2.size(); p++) {
            if ((t2[p] == '0') && (flag2 == 0)) {
              u = u * 10;
              if (t2[p + 1] != '0') flag2 = 1;
            }
          }
        }
        y = (float)(calculate(t1));
        z = (float)(calculate(t2));
        if (z < 10.0)
          z = z / (10 * u);
        else if (z < 100.0)
          z = z / (100 * u);
        else if (z < 1000.0)
          z = z / (1000.0 * u);
        else
          z = z / (10000.0 * u);
        result = y + z;
        if (p[p.size() - 2] == 'K')
          result = result * 1000;
        else if (p[p.size() - 2] == 'N')
          result = ((double)(result)) / 1000000000;
        else if (p[p.size() - 2] == 'U')
          result = ((double)(result)) / 1000000;
        else if (p[p.size() - 2] == 'M')
          result = ((double)(result)) / 1000;
        else
          result = result;
      } else {  // cout<<p.size()-2<<endl;
        if (p[p.size() - 2] == 'K')
          result = calculate(t) * 1000;
        else if (p[p.size() - 2] == 'N')
          result = ((double)(calculate(t))) / 1000000000;
        else if (p[p.size() - 2] == 'U')
          result = ((double)(calculate(t))) / 1000000;
        else if (p[p.size() - 2] == 'M')
          result = ((double)(calculate(t))) / 1000;
        else
          result = calculate(t);
      }

      // cout<<t<<" sdf"<<endl;
      value[8].push_back(result);
    }

    if ((data[9][i][0] <= '9') && (data[9][i][0] >= '0')) {
      t = data[9][i];
      float result;
      // cout<<t<<" sdf"<<endl;
      t = number(t);
      bool found = false;
      for (int r = 0; r < t.size(); r++) {
        if (t[r] == '.') found = true;
      }
      int x = t.find(".");
      if (found == true) {
        string t1, t2;
        float y, z, u = 1, flag2 = 0;
        t1 = t.substr(0, x);
        t2 = t.substr(x + 1);
        if (t2[0] == '0') {
          for (int p = 0; p < t2.size(); p++) {
            if ((t2[p] == '0') && (flag2 == 0)) {
              u = u * 10;
              if (t2[p + 1] != '0') flag2 = 1;
            }
          }
        }
        y = (float)(calculate(t1));
        z = (float)(calculate(t2));
        if (z < 10.0)
          z = z / (10 * u);
        else if (z < 100.0)
          z = z / (100 * u);
        else if (z < 1000.0)
          z = z / (1000.0 * u);
        else
          z = z / (10000.0 * u);
        result = y + z;
      } else
        result = calculate(t);
      // cout<<t<<" sdf"<<endl;
      value[9].push_back(result);
    }
  }
  // for(int j=0;j<10;j++)
  // {
  // for(int i=0;i<index;i++)
  // 	{
  // 		cout<<value[j][i]<<" ";
  // 	}
  // 	cout<<endl;
  //    }

  //	REMOVING THE AMBGUITY OF DOUBLE READS OF LAST LINE. WHICH GENERALLY
  //HAPPENS WHEN A FILE IS READ
  if ((value[0][index - 1] == value[0][index - 2]) &&
      (value[1][index - 1] == value[1][index - 2])) {
    index = index - 1;
  }
  string R1, R2;
  // CALLING THE SOLVE PART AND GETTING IT IN R1,WHATEVER IT RETURNS.
  R1 = solve_circuit(value, data, index);
  // CALLING THE DRAW PART AND GETTING IT IN R2,WHATEVER IT RETURNS.
  R2 = draw_instruction(value, data, index);
  ofile.open("results.txt");  // MAKING RESULT.TXT FILE.
  ofile << R1;                // WRITING DATA IN IT.
  ofile.close();
  ofile.open("top.svg");  // MAKING TOP.SVG FILE.
  ofile << R2;            // WRITING DATA IN IT.
  ofile.close();
  cout << "SUCCESSFULLY COMPILED!!!\nTHE CIRCUIT IS IN TOP.SVG\nTHE RESULT OF "
          "THE CIRCUIT IS IN RESULTS.TXT\n";

  return 0;
}
////////////////////////
// END OF MAIN FUNCTION//
////////////////////////