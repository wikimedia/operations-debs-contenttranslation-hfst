@echo off

for %%P IN (hfst-xfst, hfst-lexc, hfst-lookup, hfst-optimized-lookup, hfst-pmatch2fst, hfst-pmatch, hfst-proc, hfst-twolc.bat) DO call %%P --help >NUL 2>NUL && echo %%P help message: ok && call %%P --version >NUL 2>NUL && echo %%P version message: ok

@echo on

hfst-xfst --silent -F test.xfst

type test_xfst_result.txt | hfst-lookup foobar.hfst --pipe-mode=input

type test_xfst_result.txt | hfst-optimized-lookup -w foobar.olw --pipe-mode=input

hfst-proc foobar.olw test_xfst_result.txt output_from_proc && type output_from_proc

hfst-lexc test.lexc > lexc.hfst

type test_lexc_result.txt | hfst-lookup lexc.hfst --pipe-mode=input

call hfst-twolc.bat test.twolc > twolc.hfst

type test_twolc_result.txt | hfst-lookup twolc.hfst --pipe-mode=input

hfst-pmatch2fst --verbose test.pmatch > pmatch.hfst

echo ^^^^
echo test hfst-pmatch manually and copy input from test_pmatch_result.txt
echo ^^^^
