import os
import sys
import re

# Imprime as saÃ­das do programa e do gabarito
output = True

path = os.path.dirname(os.path.abspath(__file__))
os.chdir(path)

r = re.compile(r't\d.py')
for file in os.listdir():
    if r.match(file):
        labfile = file
        break
else:
    print("CÃ³digo do laboratÃ³rio nÃ£o encontrado.")
    exit(0)

i = 1
testfile = "arq" + "{:02d}".format(i) + ".in"

while (os.path.exists(testfile)):
    resfile = "arq" + "{:02d}".format(i) + ".res"
    if not os.path.exists(resfile):
        print("Arquivo", resfile, "nÃ£o encontrado.")
        sys.exit()

    outfile = "arq" + "{:02d}".format(i) + ".out"
    if (os.path.exists(outfile)):
        answer = input("Arquivo " + outfile + " existente. Pode s er sobrescrito (S/n)?")
        if answer == "n" or answer == "N":
            sys.exit()

    difffile = "arq" + "{:02d}".format(i) + ".diff"
    if (os.path.exists(difffile)):
        answer = input("Arquivo " + difffile + " existente. Pode ser sobrescrito (S/n)?")
        if answer == "n" or answer == "N":
            sys.exit()

    os.system("python3 " + labfile + " < " + testfile + " > " + outfile)
    if os.system("diff " + outfile + " " + resfile + " > " + difffile) == 0:
        print("Teste ", "{:02d}".format(i), ": resultado correto")
    else:
        print("Teste ", "{:02d}".format(i), ": resultado incorreto")
        # if output:
        #     # os.system("cat " + difffile)
        #     print(">>> Sua resposta:")
        #     os.system("cat " + outfile)
        #     print(">>> Resposta correta:")
        #     os.system("cat " + resfile)

    os.remove(outfile)
    os.remove(difffile)
    i = i + 1
    testfile = "arq" + "{:02d}".format(i) + ".in"