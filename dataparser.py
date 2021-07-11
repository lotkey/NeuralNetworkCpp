FEATUREFILENAME: str = "./guitar_di.txt"
LABELFILENAME: str = "./guitar_processed.txt"
OUTPUTFILENAME: str = "./data.txt"

numFeatures: int = 500
featureFile = open(FEATUREFILENAME, 'r')
labelFile = open(LABELFILENAME, 'r')
outputFile = open(OUTPUTFILENAME, 'w')
features = list()
labels = list()
output = list()
string: str = ""

features = featureFile.readlines()
labels = labelFile.readlines()
featureFile.close()
labelFile.close()

for i in range(numFeatures, 1000):
    string += labels[i - numFeatures].rstrip() + ","
    for j in range(0, numFeatures):
        string += features[i - (numFeatures - j)].rstrip() + ","
    string += "\n"

outputFile.write(string)
outputFile.close()
