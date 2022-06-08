import random

max_sequence_length = 150
filename = 1

for n in range(5, max_sequence_length + 1, 10):
  for m in range(5, max_sequence_length + 1, 10):

    file = f"./dnaSequences/dna{filename}.seq"
    f = open(file, 'w')
    seq=[
        ''.join(random.choices(['A','T','C','G','-'],k=n))+'\n',
        ''.join(random.choices(['A','T','C','G','-'],k=m))]
    f.writelines(seq)
    f.close()
    filename += 1
