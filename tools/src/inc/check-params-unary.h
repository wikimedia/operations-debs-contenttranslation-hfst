//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, version 3 of the License.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

    if (!inputNamed)
      {
        if ((argc - optind) == 1)
          {
            inputfilename = hfst_strdup(argv[optind]);
            inputfile = ::hfst_fopen(inputfilename, "r");
            if (inputfile == stdin)
              {
                free(inputfilename);
                inputfilename = hfst_strdup("<stdin>");
              }
          }
        else if ((argc - optind) > 1)
          {
            error(EXIT_FAILURE, 0,
                  "no more than one transducer file may be given");
          }
        else
          {
            inputfile = stdin;
            inputfilename = hfst_strdup("<stdin>");
          }
      }
    else
      {
        if ((argc - optind) > 0)
          {
            error(EXIT_FAILURE, 0,
                  "no more than one transducer filename may be given");
          }
      }

