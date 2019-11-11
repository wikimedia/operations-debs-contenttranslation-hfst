prefix = /usr/local
datapath = $(prefix)/share/finnish-tagtools
binpath = $(prefix)/bin

check:
	test/test-local.sh

check-installed:
	test/test-installation.sh

install:
	sed -e s,TAG=tag,TAG=$(datapath),g \
		< finnish-postag > $(binpath)/finnish-postag
	sed -e s,TAG=tag,TAG=$(datapath),g \
		< finnish-nertag > $(binpath)/finnish-nertag
	sed -e s,TAG=tag,TAG=$(datapath),g \
		< finnish-tokenize > $(binpath)/finnish-tokenize
	chmod 0755 $(binpath)/finnish-postag
	chmod 0755 $(binpath)/finnish-nertag
	chmod 0755 $(binpath)/finnish-tokenize
	install -m 0775 -d $(datapath)
	install -m 0775 tag/filter_lemmas --target-directory=$(datapath)
	install -m 0775 tag/finnpos-label --target-directory=$(datapath)
	install -m 0775 tag/finnpos-ratna-feats.py --target-directory=$(datapath)
	install -m 0775 tag/finnpos-restore-lemma.py --target-directory=$(datapath)
	install -m 0775 tag/hfst-pmatch --target-directory=$(datapath)
	install -m 0775 tag/hfst-tokenize --target-directory=$(datapath)
	install -m 0775 tag/move_tags --target-directory=$(datapath)
	install -m 0775 tag/omorfi2finnpos.py --target-directory=$(datapath)
	install -m 0775 tag/normalize-lemmas.py --target-directory=$(datapath)
	install -m 0775 tag/prefilt_tags --target-directory=$(datapath)
	install -m 0775 tag/add_boundaries --target-directory=$(datapath)
	install -m 0775 tag/remove_exc --target-directory=$(datapath)
	install -m 0664 tag/freq_words --target-directory=$(datapath)
	install -m 0664 tag/lemma-errors.tsv --target-directory=$(datapath)
	install -m 0664 tag/ftb.omorfi.model --target-directory=$(datapath)
	install -m 0664 tag/omorfi_tokenize.pmatch --target-directory=$(datapath)
	install -m 0664 tag/omorfi.tagtools.optcap.hfst --target-directory=$(datapath)
	install -m 0664 tag/proper_tagger_ph1.pmatch --target-directory=$(datapath)
	install -m 0664 tag/proper_tagger_ph2.pmatch --target-directory=$(datapath)

uninstall:
	rm -f $(binpath)/finnish-postag
	rm -f $(binpath)/finnish-nertag
	rm -f $(binpath)/finnish-tokenize
	rm -rf $(datapath)
