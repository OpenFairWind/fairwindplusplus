import json
import sys
import shutil

template_path = "/Users/raffaelemontella/CLionProjects/fairwindplusplus/sdk/templates/app/"

json_file = sys.argv[1]
output_root = sys.argv[2]

print (json_file)
print (output_root)

manifest_data = json.load(open(json_file))

from datetime import date

today = date.today()

# dd/mm/YY
d1 = today.strftime("%d/%m/%Y")

values = { 
  "__Appname__":manifest_data["Name"],
  "__appname__":manifest_data["Name"].lower(),
  "__APPNAME__":manifest_data["Name"].upper(),
  "__date__":d1,
  "__vendor__":manifest_data["Vendor"],
  "__copyright__":manifest_data["Copyright"],
  "__license__":manifest_data["License"],
  "__description__":manifest_data["Description"],
  "__url__":manifest_data["Url"],
  "__id__":manifest_data["FairWind"]["App"]["Id"],
  "__email__":manifest_data["FairWind"]["App"]["Email"],
  "__namespace__":manifest_data["FairWind"]["App"]["Id"].replace(".","::")
}

print(values)

output_path = output_root + "/" + values["__appname__"]

import os
if not os.path.exists(output_path):
  os.makedirs(output_path)

shutil.copyfile(json_file, output_path + "/manifest.json")

for entry in os.scandir(template_path):
  if entry.is_file():
    dst_file_name = entry.name 
    for key in values.keys():
        dst_file_name=dst_file_name.replace(key,values[key])

    dst_file = open(output_path + "/" + dst_file_name,'w')
    src_file = open(entry.path, 'r')

    lines = src_file.readlines()

    for line in lines:
      for key in values.keys():
        line=line.replace(key,values[key])
      dst_file.write(line)

    src_file.close()
    dst_file.close()

