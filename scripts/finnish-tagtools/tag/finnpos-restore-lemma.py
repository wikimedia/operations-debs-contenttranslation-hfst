#! /usr/bin/env python3

from sys import stdin, stdout, stderr, argv

HASH="<HASH>"
for_ner = False

def get_proptags(label_lemma_pairs):
    proptags = set()
    for label, lemma in label_lemma_pairs:
        for part in label.split("|"):
            if part.startswith("[PROP="):
                proptags.add(part)
    if len(proptags) != 0:
        return ''.join(sorted(proptags))
    return "_"

def is_subset(tags1, tags2):
    parts1 = tags1.split("|")
    parts2 = tags2.split("|")
    for part in parts1:
        if part not in parts2:
            return False
    return True

def is_exact_match(tags1, tags2):
    parts1 = tags1.split("|")
    parts2 = tags2.split("|")
    if len(tags1) != len(tags2):
        return False
    for part in parts1:
        if part not in parts2:
            return False
    return True

if "ner" in argv:
    for_ner = True

for line in stdin:
    line = line.strip()

    if line == '':
        print('')
        stdout.flush()
    else:
        wf, feats, lemma, label, ann = line.split('\t')

        lemmas = ann
        if ann.find(' ') != -1:
            lemmas = ann[:ann.find(' ')]
            ann = ann[ann.find(' ') + 1:]

        ann = "_"
        if lemmas != '_':
            lemmas = eval(lemmas)
            lemma_candidate = None
            
            for this_label, this_lemma in lemmas:
                if is_exact_match(label, this_label):
                    lemma = this_lemma
                    lemma_candidate = None
                    break
                elif lemma_candidate is None and is_subset(label, this_label):
                    lemma_candidate = this_lemma
            if lemma_candidate:
                lemma = lemma_candidate
            elif '[PROPER=PROPER]' in lemmas[0][0]:
                label = lemmas[0][0]
                lemma = lemmas[0][1]
            if '[PROPER=PROPER]' in label:
                ann = get_proptags(lemmas)
        lemma = lemma.replace(HASH, "#")
        if for_ner:
            lemma = lemma.lower()
            label = label.replace('|', '')
        print('%s\t%s\t%s\t%s\t%s' % (wf, feats, lemma, label, ann))
