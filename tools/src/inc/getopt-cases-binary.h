  //       This program is free software: you can redistribute it and/or modify
//       it under the terms of the GNU General Public License as published by
//       the Free Software Foundation, version 3 of the License.
//
//       This program is distributed in the hope that it will be useful,
//       but WITHOUT ANY WARRANTY; without even the implied warranty of
//       MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//       GNU General Public License for more details.
//
//       You should have received a copy of the GNU General Public License
//       along with this program.  If not, see <http://www.gnu.org/licenses/>.

// common-binary-cases.h
case '1':
  firstfilename = hfst_strdup(optarg);
  firstfile = hfst_fopen(firstfilename, "r");
  if (firstfile == stdin) {
    free(firstfilename);
    firstfilename = hfst_strdup("<stdin>");
    is_input_stdin = true;
  }
  firstNamed = true;
  break;
case '2':
  secondfilename = hfst_strdup(optarg);
  secondfile = hfst_fopen(secondfilename, "r");
  if (secondfile == stdin) {
    free(secondfilename);
    secondfilename = hfst_strdup("<stdin>");
    is_input_stdin = true;
  }
  secondNamed = true;
  break;
case 'C':
  allow_transducer_conversion=false;
  break;
