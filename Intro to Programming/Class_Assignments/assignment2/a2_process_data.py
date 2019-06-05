#######################################################
### Please ignore the lines of code in this section.
### It loads the contents of a CSV file for you.
### The file's name should be a2_input.csv.
### You do not need to know how it works.
#######################################################

import csv

contents = []
with open("a2_input.csv") as input_file:
    for row in csv.reader(input_file):
        contents = contents + [row]

#######################################################
### Do your data processing below.
### The below code gives some examples
### of how to access the data.
### Print your results using the print function.
#######################################################


print("""<!DOCTYPE html>
<html lang=\"en\">
<head>
    <meta charset=\"utf-8\" />
    <title>Unemployment Rates</title>
    <style>
        table, td {
            border: 3px solid black;
            border-collapse: collapse;
        }
        
        table {
            width: 100%;
        }
        
        td {
            text-align: center;
        }
        
        #source {
            font-size: 0.8em;
            text-style: italic;
        }
        th {
        width: 100%;
        }

        #year, #country {
            width: 50%;        
        }
    </style>
</head>
<body>
<h1>Unemployment Rates</h1>""")
#print("This assignment (assignment 2) has been finished.")
#print(contents)
#print(contents[0])
#print(contents[0][0])
#print(type(contents))
#print(type(contents[0]))
#print(type(contents[0][0]))
#print(contents[20][5])
#print(contents[12][8])
#country_num = len(contents[0]) - 1
#year_num = len(contents) - 2
#print(turkey_average)
#first = contents[0][3] + contents[0][30]
#second = 3 * contents[0][80]
#print(first)
#print(second)
#print(type(first), type(second))
#help(first)
#help(type(first))
print("""<table>""")
for i in range(29):
    print("<tr>")
    for j in range(89):
        if i != 0:
            contents[i][j] = contents[i][j].replace(",", ".")
        print("<td>"+ contents[i][j] + "</td>")
    print("</tr>")
print("</table>")

turkey_average = 0.0
turkey_year = 0.0
for i in range(len(contents)):
    if contents[i][80].isdigit():
        turkey_average += float(contents[i][80])
        turkey_year += 1.0
turkey_average = turkey_average / turkey_year

average_by_year = []
real_data_by_year = []
real_data = 0
average = 0

for i in range(1, 29):
    for j in range(1, 89):
        if contents[i][j] != "NA":
            average += float(contents[i][j])
            real_data += 1
        else:
            continue
    average_by_year.append(average)
    average = 0
    real_data_by_year.append(real_data)
    real_data = 0
    
for i in range(len(average_by_year)):
    average_by_year[i] = average_by_year[i] / real_data_by_year[i]
    
average_country = []
real_data_country = []
real_data = 0
average = 0

for i in range(1, 89):
    for j in range(1, 29):
        if contents[j][i] != "NA":
            average += float(contents[j][i])
            real_data += 1
        else:
            continue
    average_country.append(average)
    average = 0
    real_data_country.append(real_data)
    real_data = 0
    
for i in range(len(average_country)):
    if real_data_country[i] != 0:
        average_country[i] = average_country[i] / real_data_country[i]
    else:
        average_country[i] = "NA"


print("""
<p id="source">Data provided by <a href="https://datacatalog.worldbank.org/dataset/global-economic-monitor">
The World Bank</a></p>
<p>After analysing our data, we created two new tables.</p>
<h3>Average Unemployment by Year</h3>""")

print("""<table>"""
"""<th id="year">Years</th>
<th>Average Unemployment</th>""")
for i in range(len(average_by_year)):
    print("""<tr>
    <td>{}</td>
    <td>{}</td>
</tr>""".format(contents[i + 1][0], round(average_by_year[i], 2)))
print("</table>")

print("<h3>Average Unemployment by Country</h3>")

print("""<table>"""
"""<th id="country">Countries</th>
<th>Average Unemployment</th>""")
for i in range(len(average_country)):
    if average_country[i] != "NA":
        print("""<tr>
    <td>{}</td>
    <td>{}</td>
</tr>""".format(contents[0][i + 1], round(average_country[i], 2)))  
    else:
        print("""<tr>
    <td>{}</td>
    <td>NA</td>
</tr>""".format(contents[0][i + 1]))

print("</table>")

print("""</body>
</html>""")



