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

    case '?':
        print_short_help();
        if (optopt == 'c')
          {
            error(EXIT_FAILURE, 0, "Option -%c requires an argument.\n",
                  optopt);
          }
        else if (isprint (optopt))
          {
            error(EXIT_FAILURE, 0, "Unknown option `-%c'.\n", optopt);
          }
        else
          {
            error(EXIT_FAILURE, 0, "Unknown option");
          }
        return EXIT_FAILURE;
        break;
    case ':':
        print_short_help();
        error(EXIT_FAILURE, 0, "Option -%c requires an argument", optopt);
        return EXIT_FAILURE;
        break;
    default:
        print_short_help();
        error(EXIT_FAILURE, 0 , "invalid option -%c", c);
        return EXIT_FAILURE;
        break;

