#!/usr/bin/python
import json
import csv
import geojson
import tempfile

def removeDuplicate(array):
    seen = set()
    result = []
    for item in array:
        if item not in seen:
            seen.add(item)
            result.append(item)
    return result

def getDataForCountry(country_name):
    # Open the CSV file
    with open('../data/wine-data.csv', 'r') as csv_data_file:
        wine_data = csv.reader(csv_data_file, delimiter=',', quotechar='"')
        num_of_diff_wine = 0
        # 80-84 poor wine
        poor = 0
        # 84-88 fair wine
        fair = 0
        # 88-92 good wine
        good = 0
        # 92-96 very good wine
        very_good = 0
        # 96-100 excellent wine
        excellent = 0
        producers_list = []
        for row in wine_data:
            if row[1] == country_name:
                num_of_diff_wine += 1
                #print row[10].decode('string_escape')
                producers_list.append(row[10].decode('string_escape'))

                # find the classification of the wine
                if 80 <= int(row[4]) < 84:
                    poor += 1
                if 84 <= int(row[4]) < 88:
                    fair += 1
                if 88 <= int(row[4]) < 92:
                    good += 1
                if 92 <= int(row[4]) < 96:
                    very_good += 1
                if 96 <= int(row[4]) <= 100:
                    excellent += 1
        producers = removeDuplicate(producers_list)
        # Create json object
        result = {'name': country_name, 'num_of_wines': num_of_diff_wine, 'poor_wine': poor, 'fair_wine': fair, 'good_wine': good,
                  'veryGood_wine': very_good, 'excellent_wine': excellent, 'producers': producers}
        return result

def main():
    with open('../data/world-countries.geojson') as geojson_data_file:
        data = geojson.load(geojson_data_file)

    objects = data['features']
    i = 0
    for obj in objects:
        try:
            country_name = obj['properties']['name']
            if country_name == 'United States of America':
                country_name = 'US'
            country_data = getDataForCountry(country_name)
            obj['properties'] = country_data
        except Exception as error:
            print('Error happened: ', error)

    output_filename = 'outputFile.geojson'
    with open(output_filename, 'wb') as output_file:
        # output_file.write('{\n"type": "FeatureCollection",')
        json.dump(data, output_file, indent=2)

if __name__ == '__main__':
    main()