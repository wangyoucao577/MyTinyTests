
# use an offical python runtime as a parent image
FROM python:2.7-slim

# set the working directory to /app
WORKDIR /app

# copy the current directory contents into the container at /app
ADD . /app

# Run app.py when the container launches
CMD ["python", "app.py"]


