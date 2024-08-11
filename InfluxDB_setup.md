# InfluxDB
Guide can be found [here](https://docs.influxdata.com/influxdb/v1/guides/downsample_and_retain/).

Create the database with
```
CREATE DATABASE garduino
```


## Retention policies (RPs)

```
CREATE RETENTION POLICY "1_hour" ON "GarduinoInfluxDB" DURATION 60m REPLICATION 1 DEFAULT;
```

```
CREATE RETENTION POLICY "24_hours" ON "GarduinoInfluxDB" DURATION 24h REPLICATION 1;
```

```
CREATE RETENTION POLICY "1_year" ON "GarduinoInfluxDB" DURATION 52w REPLICATION 1;
```

## Continuous queries (QCs)

```
CREATE CONTINUOUS QUERY "cq_5m" ON "GarduinoInfluxDB" BEGIN SELECT mean(*) INTO "24_hours"."garduino_5minutely" FROM "1_hour"."garduino" GROUP BY time(5m) END
```

```
CREATE CONTINUOUS QUERY "cq_1h" ON "GarduinoInfluxDB" BEGIN SELECT mean(*) INTO "1_year"."garduino_hourly" FROM "24_hours"."garduino_5minutely" GROUP BY time(60m) END
```

## Write to DB
```
curl -i -XPOST 'http://localhost:8086/api/v2/write?bucket=GarduinoInfluxDB/1_hour&precision=s' \
  --data-raw 'garduino soil0=250,air_temperature=24.4,air_humidity=80.9 1711484742'
```