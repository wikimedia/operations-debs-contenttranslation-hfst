# A very simple fallback tokenizer
import string

def print_tokenize(line):
    if line == "":
        return
    parts = line.split()
    for part in parts:
        thispart = part
        while thispart != "" and thispart[0] in string.punctuation:
            print(thispart[0])
            thispart = thispart[1:]
        endpunct_queue = []
        while thispart != "" and thispart[-1] in string.punctuation:
            if thispart.endswith("..."):
                endpunct_queue.append("...")
                thispart = thispart[:-3]
            else:
                endpunct_queue.append(thispart[-1])
                thispart = thispart[:-1]
        if thispart != "":
            print(thispart)
        for endpunct in endpunct_queue[::-1]:
            print(endpunct)
    print("")

while True:
    try:
        print_tokenize(input())
    except EOFError:
        break
