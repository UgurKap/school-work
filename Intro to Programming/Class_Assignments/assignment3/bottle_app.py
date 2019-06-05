
#####################################################################
### Assignment skeleton
### You can alter the below code to make your own dynamic website.
### The landing page for assignment 3 should be at /
#####################################################################

from bottle import route, run, default_app, debug, get, post, request
import csv

contents = []
with open("a3_input.csv") as input_file:
    for row in csv.reader(input_file):
        contents = contents + [row]
        

last_search = ""

ecoun = """AUSTRALIA 	
AUSTRIA 	
BELGIUM 	
CANADA 	
CHILE 	
CZECH REPUBLIC 	
DENMARK 	
ESTONIA 	
FINLAND 	
FRANCE 	
GERMANY 	
GREECE 	
HUNGARY 	
ICELAND
IRELAND 	
ISRAEL 	
ITALY 	
JAPAN 	
Korea, Rep. 	
LATVIA 	
LUXEMBOURG 	
MEXICO 	
NETHERLANDS 	
NEW ZEALAND 	
NORWAY 	
POLAND 	
PORTUGAL 	
SLOVAKIA 	
SLOVENIA 	
SPAIN 	
SWEDEN 	
SWITZERLAND 	
TURKEY 	
UNITED KINGDOM 	
UNITED STATES"""



style = """

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

#stopdate {
    margin-bottom: 1em;
}

#header {
    text-decoration: none;
}
"""

def htmlify(title,text):
    page = """
<!doctype html>
<html lang="en">
    <head>
        <meta charset="utf-8" />
        <title>{}</title>
        <style>
            {}
        </style>
    </head>
    <body>
    <a href="/" id="header"><h1>Unemployment Rates</h1></a>
    {}
    <p id="source">Data provided by <a href="https://datacatalog.worldbank.org/dataset/global-economic-monitor">
The World Bank</a></p>
    </body>
</html>""".format(title, style, text)
    return page 

def generate_table(search = "", oecd=False, start=1, stop=28, date="all"):
    global last_search
    last_search = search
    table = "<table>"
    for i in range(29):
        table += "<tr>"
        for j in range(89):
            if search.lower() in contents[0][j].lower() or contents[0][j] == "":
                if i != 0:
                    contents[i][j] = contents[i][j].replace(",", ".")
                if oecd == True:
                    if date == "all":
                        if contents[0][j].lower() in ecoun.lower():
                            if (int(start) <= i and i<= int(stop)) or i == 0:
                                table += ("<td>"+ contents[i][j] + "</td>")
                    if date == "20":
                        if contents[0][j].lower() in ecoun.lower() and i < 12:
                            if (int(start) <= i and i<= int(stop)) or i == 0:
                                table += ("<td>"+ contents[i][j] + "</td>")
                    if date == "21":
                        if contents[0][j].lower() in ecoun.lower() and (i > 11 or i == 0):
                            if (int(start) <= i and i<= int(stop)) or i == 0:
                                table += ("<td>"+ contents[i][j] + "</td>")
                else:
                    if date == "all":
                        if (int(start) <= i and i<= int(stop)) or i == 0:
                                table += ("<td>"+ contents[i][j] + "</td>")
                    if date == "20":
                        if i < 12:
                            if (int(start) <= i and i<= int(stop)) or i == 0:
                                table += ("<td>"+ contents[i][j] + "</td>")
                    if date == "21":
                        if i > 11 or i == 0:
                            if (int(start) <= i and i<= int(stop)) or i == 0:
                                table += ("<td>"+ contents[i][j] + "</td>")
                #table += ("<td>"+ contents[i][j] + "</td>")
        table += "</tr>"
    table += "</table>"
    return  table

def search_box():
    html = """<hr>
<form action="/search" method="get">
<div id="searchbox">
        <label for="Search"><h3>Search Country:</h3></label>
        <input type="search" id="query" name="query">
        <button type="submit">Search</button>
</div>
</form>
<hr>
    """
    return html

def filtering():
    html = """
<form action="/filter" method="post">
    <div id="checkbox">
        <h3>Filter Countries</h3>
        <label for="OECD">Show only OECD Countries</label>
        <input type="checkbox" id="oecd" name="oecd" value="True">
        <input type="hidden" id="search" name="search" value="">
    </div>
    <div id="radios">
        <h3>Filter Dates</h3>
        <label for="20">Show dates from 20th century</label>
        <input type="radio" id="20" name="date" value="20">
        <label for="21">Show dates from 21st century</label>
        <input type="radio" id="21" name="date" value="21">
        <label for="all">Show all the dates</label>
        <input type="radio" id="all" name="date" value="all" checked="checked">
    </div>
    <div id="select">
    <h3>Date Ranges</h3>
        <select id="startdate" name="start">
            <option name="start" value="1" selected="selected">1990</option>
            <option name="start" value="2">1991</option>
            <option name="start" value="3">1992</option>
            <option name="start" value="4">1993</option>
            <option name="start" value="5">1994</option>
            <option name="start" value="6">1995</option>
            <option name="start" value="7">1996</option>
            <option name="start" value="8">1997</option>
            <option name="start" value="9">1998</option>
            <option name="start" value="10">1999</option>
            <option name="start" value="11">2000</option>
            <option name="start" value="12">2001</option>
            <option name="start" value="13">2002</option>
            <option name="start" value="14">2003</option>
            <option name="start" value="15">2004</option>
            <option name="start" value="16">2005</option>
            <option name="start" value="17">2006</option>
            <option name="start" value="18">2007</option>
            <option name="start" value="19">2008</option>
            <option name="start" value="20">2009</option>
            <option name="start" value="21">2010</option>
            <option name="start" value="22">2011</option>
            <option name="start" value="23">2012</option>
            <option name="start" value="24">2013</option>
            <option name="start" value="25">2014</option>
            <option name="start" value="26">2015</option>
            <option name="start" value="27">2016</option>
            <option name="start" value="28">2017</option>
        </select>
        <span id="dash">-</span>
        <select id="stopdate" name="stop">
            <option name="stop" value="1">1990</option>
            <option name="stop" value="2">1991</option>
            <option name="stop" value="3">1992</option>
            <option name="stop" value="4">1993</option>
            <option name="stop" value="5">1994</option>
            <option name="stop" value="6">1995</option>
            <option name="stop" value="7">1996</option>
            <option name="stop" value="8">1997</option>
            <option name="stop" value="9">1998</option>
            <option name="stop" value="10">1999</option>
            <option name="stop" value="11">2000</option>
            <option name="stop" value="12">2001</option>
            <option name="stop" value="13">2002</option>
            <option name="stop" value="14">2003</option>
            <option name="stop" value="15">2004</option>
            <option name="stop" value="16">2005</option>
            <option name="stop" value="17">2006</option>
            <option name="stop" value="18">2007</option>
            <option name="stop" value="19">2008</option>
            <option name="stop" value="20">2009</option>
            <option name="stop" value="21">2010</option>
            <option name="stop" value="22">2011</option>
            <option name="stop" value="23">2012</option>
            <option name="stop" value="24">2013</option>
            <option name="stop" value="25">2014</option>
            <option name="stop" value="26">2015</option>
            <option name="stop" value="27">2016</option>
            <option name="stop" value="28" selected="selected">2017</option>
        </select>
    </div>
    <button type="submit">Filter</button>
</form>
<hr>
"""
    return html
    
@route("/")
@route("/index")
def index():
    body = generate_table()
    search = search_box()
    filters = filtering()
    return htmlify("Unemployment Rates", search + filters + body)

@get("/search")
def search_func():
    search = request.query.query
    body = search_box() + filtering() + generate_table(search)
    return htmlify("Unemployment Rates", body)

@post("/filter")
def filter_func():
    global last_search
    eco = request.forms.get("oecd")
    start = request.forms.get("start")
    stop = request.forms.get("stop")
    date = request.forms.get("date")
    try:
        body = search_box() + filtering() + generate_table(search=last_search, oecd=bool(eco), start = start, stop = stop, date=date)
    except:
        body = search_box() + filtering() + generate_table(search=last_search, start = start, stop = stop, date=date)
    last_search = request.forms.get("search")
    return htmlify("Unemployment Rates", body)



#####################################################################
### Don't alter the below code.
### It allows this website to be hosted on Heroku
### OR run on your computer.
#####################################################################

# This line makes bottle give nicer error messages
debug(True)
# This line is necessary for running on Heroku
app = default_app()
# The below code is necessary for running this bottle app standalone on your computer.
if __name__ == "__main__":
  run(reloader = False)
  


