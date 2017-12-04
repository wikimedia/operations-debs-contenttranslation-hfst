#! /usr/bin/env python3

from sys import stdin, stdout, argv

for_finer = False
if len(argv) > 1 and argv[1] == "--finer":
    for_finer = True

def part_count(lemma):
    return lemma.count('#')

def compile_dict(label_lemma_pairs):
    res = {}

    for label, lemma in label_lemma_pairs:
        if label in res:
            old_lemma = res[label]

            if part_count(old_lemma) > part_count(lemma):
                res[label] = lemma
        else:
            res[label] = lemma

    return res

def get_proptags(label2lemma):
    proptags = set()
    for label in label2lemma.keys():
        for part in label.split("|"):
            if part.startswith("[PROP="):
                proptags.add(part)
    return ''.join(list(proptags))

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
        else:
            ann = '_'
        
        lemma_dict = {}
        if lemmas != '_':
            lemma_dict = compile_dict(eval(lemmas))

        if for_finer and "PROPER" in label:
            PROPtags = get_proptags(lemma_dict)
            if PROPtags != '':
                ann = PROPtags
        
        if label in lemma_dict:
            lemma = lemma_dict[label]
            lemma = lemma.lower()
            lemma = lemma.replace('#','')

        if for_finer:
            print('%s\t%s\t%s\t%s' % (wf, lemma,
                                      label.replace('|',''),
                                      ann.replace('|', '')))
        else:
            print('%s\t%s\t%s\t%s\t%s' % (wf, feats, lemma, label, ann))
