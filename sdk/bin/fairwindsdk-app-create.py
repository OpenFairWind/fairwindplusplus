#! python

import os
import json
import sys
import getopt
import shutil
import logging
from datetime import date

# Set the logging default level
logging.basicConfig(level=logging.INFO)


# Main function
def main(argv):

  # The path of the FairWind SDK directory
  fairwind_sdk_home = os.getenv('FAIRWINDSDK_HOME')

  # The application manifest file
  manifest_json_file = ""

  # The output root (where the app will be created)
  output_root = ""

  # Try to get options and arguments
  try:
    # Get the options and the arguments
    opts, args = getopt.getopt(argv,"hs:m:o:",["fairwindsdk-home=", "manifest=", "output-root="])

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

    # Check if the option is -s or --fairwindsdk-home
    elif opt in ("-s", "--fairwindsdk-home"):

      # Get the fairwind sdk directory from the argument
      fairwind_sdk_home = arg

    # Check if the option is -m or --manifest
    elif opt in ("-m", "--manifest"):

      # Get the manifest json file from the argument
      manifest_json_file = arg

    # Check if the option is -o or --output-root
    elif opt in ("-o", "--output-root"):

      # Get the output root from the argument
      output_root = arg


  if fairwind_sdk_home is None or fairwind_sdk_home=="":
    logging.error("FAIRWINDSDK_HOME not set or -s / --fairwindsdk-home parameters not in the command line.")
    show_usage()
    exit(2)

  if manifest_json_file is None or manifest_json_file=="":
    logging.error("Manifest file not set")
    show_usage()
    sys.exit(2)

  if not os.path.isfile(manifest_json_file):
    logging.error("Manifest file doesn't exist!")
    show_usage()
    sys.exit(2)

  if output_root is None or output_root=="":
    logging.error("Output root file not set")
    show_usage()
    sys.exit(2)

  if not os.path.isdir(output_root):
    logging.error("Output directory doesn't exist (or is not a directory)!")
    show_usage()
    sys.exit(2)

  # Get the absolute paths
  fairwind_sdk_home = os.path.abspath(fairwind_sdk_home)
  manifest_json_file = os.path.abspath(manifest_json_file)
  output_root = os.path.abspath(output_root)

  # Set the templates path
  templates_path = fairwind_sdk_home + os.sep + "templates/app"

  # Show the settings
  logging.info ("Templates path: " + templates_path)
  logging.info ("Manifest: " + manifest_json_file)
  logging.info ("Output root: " + output_root)

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

  logging.info("App name : " + values["__Appname__"])
  logging.info("namespace: " + values["__namespace__"])
  logging.info("id       : " + values["__id__"])

  # Create the output path
  output_path = output_root + "/" + values["__appname__"]

  logging.debug("Output path: " + output_path)


  # Check if the output path don't exists
  if not os.path.exists(output_path):

    # Create the output path
    os.makedirs(output_path)

  # Copy the manifest
  shutil.copyfile(manifest_json_file, output_path + os.sep + "manifest.json")

  prepare_dir(templates_path, values, output_path)

def prepare_dir(templates_path, values, output_path):

  logging.debug("prepare_dir --- templates_path: " + templates_path + " output_path:" + output_path)

  # Check if output_path don't exists
  if not os.path.isdir(output_path):

    # Create the output path
    os.makedirs(output_path)

  # For each entry in the templates directory
  for entry in os.scandir(templates_path):

    # Check if the entry is a file
    if entry.is_file():

      # Get the destination file name
      dst_file_name = fill_template(values, entry.name)

      # Check if the template file is a text file
      if (is_text_file(entry.path)):
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
      else:
        # Copy the file
        shutil.copyfile(entry.path, output_path + os.sep + dst_file_name)

    elif entry.is_dir():
      logging.debug("entry.name: "+entry.name)
      prepare_dir(templates_path+os.sep+entry.name,values,output_path+os.sep+entry.name)


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
  logging.error ('fairwindapp-create.py -t <templatepath> -m <manifestfile> -o <outputroot>')


# Check if a file is a text file
def is_text_file(file_name):

  # Define the text characters
  textchars = bytearray({7,8,9,10,12,13,27} | set(range(0x20, 0x100)) - {0x7f})

  # Define the lambda  function
  is_binary_string = lambda bytes: bool(bytes.translate(None,textchars))

  # By default read 1024 bytes
  bytes_to_check = 1024

  # If the file size is smaller than 1024, just use the whole file
  if os.path.getsize(file_name) < bytes_to_check:
    bytes_to_check = os.path.getsize(file_name)

  return not is_binary_string(open(file_name,"rb").read(bytes_to_check))


# Check if this is the main
if __name__ == "__main__":

  # Run the main function
  main(sys.argv[1:])





