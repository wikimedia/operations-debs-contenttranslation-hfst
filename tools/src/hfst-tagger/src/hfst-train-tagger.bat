@echo off
HFST_INSTALLATION_DIRECTORY\hfst-open-input-file-for-tagger.exe %* | python HFST_INSTALLATION_DIRECTORY\hfst_tagger_compute_data_statistics.py %* | HFST_INSTALLATION_DIRECTORY\hfst-build-tagger.exe %*
