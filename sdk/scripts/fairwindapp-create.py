import os
import json
import sys
import getopt
import shutil
from datetime import date

# Main function
def main(argv):

  # The path of the templates directory
  templates_path = ""

  # The application manifest file
  manifest_json_file = ""

  # The output root (where the app will be created)
  output_root = ""

  # Try to get options and arguments
  try:
    # Get the options and the arguments
    opts, args = getopt.getopt(argv,"ht:m:o:",["templates=", "manifest=", "output-root="])

  except getopt.GetoptError:

    # Show an usage message
    show_usage()

    # Exit with code 2
    sys.exit(2)

  # For each opt and arg in opts
  for opt, arg in opts:

    # Check if the option is -h
    if opt == '-h':
      # Show the usage message
      show_usage()

      # Exit
      sys.exit()

    # Check if the option is -t or --templates
    elif opt in ("-t", "--templates"):

      # Get the templates path from the argument
      templates_path = arg

    # Check if the option is -m or --manifest
    elif opt in ("-m", "--manifest"):

      # Get the manifest json file from the argument
      manifest_json_file = arg

    # Check if the option is -o or --output-root
    elif opt in ("-o", "--output-root"):

      # Get the output root from the argument
      output_root = arg

  # Show the settings
  print ("Templates path:", templates_path)
  print ("Manifest:", manifest_json_file)
  print ("Output root:", output_root)

  # Get the manifest data
  manifest_data = json.load(open(manifest_json_file))

  # Get the today date
  today = date.today()

  # Print the date as dd/mm/YY
  d1 = today.strftime("%d/%m/%Y")

  # Values from the manifest
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

  # Show the values
  print(values)

  # Create the output path
  output_path = output_root + "/" + values["__appname__"]

  # Check if the output path don't exists
  if not os.path.exists(output_path):

    # Create the output path
    os.makedirs(output_path)

  # Copy the manifest
  shutil.copyfile(manifest_json_file, output_path + "/manifest.json")

  # For each entry in the templates directory
  for entry in os.scandir(templates_path):

    # Check if the entry is a file
    if entry.is_file():

      # Get the destination file name
      dst_file_name = fill_template(values, entry.name)

      # Open the destination file
      dst_file = open(output_path + "/" + dst_file_name,'w')

      # Open the source file
      src_file = open(entry.path, 'r')

      # Read all the source file lines
      lines = src_file.readlines()

      # For each line...
      for line in lines:

        # Fill the template
        line = fill_template(values, line)

        # Write the line in the destination file
        dst_file.write(line)

      # Close the source file
      src_file.close()

      # Close the destination file
      dst_file.close()

# Perform the template filling
def fill_template(values, text):

  # For each key in the values dictionary
  for key in values.keys():

    # Perform the key replacemnt with the value
    text=text.replace(key,values[key])

  # Return the replaced text
  return text


# Show an usage text
def show_usage():
  print ('fairwindapp-create.py -t <templatepath> -m <manifestfile> -o <outputroot>')

# Check if this is the main
if __name__ == "__main__":

  # Run the main function
  main(sys.argv[1:])





