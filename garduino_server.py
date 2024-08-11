from datetime import datetime
import requests

from flask import Flask, request
import pytz

app = Flask(__name__)

def write_to_influx_db(raw_data_string):
    url = "http://localhost:8086/api/v2/write?bucket=GarduinoInfluxDB/1_hour&precision=s"
    r = requests.post(url, data=raw_data_string)


@app.route('/')
def status():
    # res = cur.execute("SELECT * FROM air_temperature ORDER BY ID DESC LIMIT 1")
    # _, timestamp, temperature = res.fetchone()
    # utc_dt = datetime.utcfromtimestamp(timestamp)
    # berlin_tz = pytz.timezone('Europe/Berlin')
    # berlin_dt = utc_dt.replace(tzinfo=pytz.utc).astimezone(berlin_tz)
    # formatted_dt = berlin_dt.strftime('%H:%M:%S %Y-%m-%d')
    return "OK" #f"It is {temperature} degress at {formatted_dt}"


@app.route('/soilmoisture', methods=['POST'])
def soil_moisture():
    if request.method == "POST":
        current_time = int(datetime.now().timestamp())
        data_string = "garduino "
        for i in range(5):
            name = f"soil{i}"
            if name in request.form:
                print(f"Writing to db {name}")
                data_string += name + "=" + request.form[name] + ","
        
        data_string += "air_temperature=" + request.form["temperature"] + ","
        data_string += "air_humidity=" + request.form["humidity"] + " "
        data_string += str(current_time)

        write_to_influx_db(data_string)

        return "Good"
    else:
        return "Bad request"

