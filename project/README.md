# CAMELIA
#### Video Demo:  https://youtu.be/qy0FTvGZQwU
#### Description:
Overview
CAMELA is a sophisticated tracking tool designed to facilitate comprehensive academic monitoring and learning assessment. 
This project is tailored to meet the needs of educational institutions, providing a seamless solution for tracking and evaluating student progress. 
The application is built with a modular structure, organized into three main directories: app, public, and .htaccess.

I choose to use the style of my own framework, so I created on from 0.

App Directory
config:
Contains configuration files for the application. Here, settings related to the database, application environment, and other parameters are defined. 
The configuration is crucial for tailoring the tool to the specific requirements of each educational institution.

controllers:
This directory holds the controller files, which are responsible for handling user requests, processing data, and interacting with the model and view components. 
Controllers play a vital role in ensuring smooth navigation and functionality within the application.

helpers:
In the helpers directory, utility functions and classes are stored to assist various parts of the application. 
These can include functions for form validation, data formatting, or any other tasks that are commonly performed across different modules.

libs:
Here, essential libraries and third-party dependencies are housed.

models:
The models directory contains files that define the structure and behavior of the data within the application. 

views:
Responsible for presenting the user interface, the views directory contains files that define the layout and structure of the application's pages. 
These files are essential for creating a user-friendly experience.

.htaccess:
The .htaccess file in the app directory is configured to enhance the security and performance of the application. 
It may include directives for URL rewriting, access control, and other server configurations.

initializer.php:
This file serves as the entry point for the application, initializing necessary components and setting up the environment. 
It ensures that the application starts with the required configurations and resources.

Public Directory
css:
Houses the cascading style sheets (CSS) used to define the visual presentation of the application.

images:
Stores image files utilized in the application. 
This includes logos, icons, and any other visual elements that enhance the overall user experience.

js:
Contains JavaScript files that provide client-side interactivity and enhance the user interface. 
Functions such as form validation, dynamic content loading, and other front-end operations are defined in these files.

.htaccess:
Similar to the app directory, the public directory's .htaccess file is responsible for configuring server settings to optimize security and performance.

index.php:
The main entry point for the public-facing side of the application. 
This file initiates the necessary processes to handle user requests and render the appropriate responses.

## System Requirements

To run this project on your local environment, make sure to meet the following system requirements:

- [XAMPP](https://www.apachefriends.org/index.html) - It is recommended to use XAMPP as the installer, which includes Apache, MySQL, and PHP, simplifying the setup of the development environment.

### Installing XAMPP

1. Download and install XAMPP from [apachefriends.org](https://www.apachefriends.org/index.html).

2. Start the Apache and MySQL servers from the XAMPP control panel.

3. Verify that the services are running correctly before proceeding.

### Database Configuration

1. Create a new database in MySQL for the project.

2. Update the configuration files in the `app/config` folder with the database connection details.

### Starting the Project

1. Clone this repository to your local machine.

2. Place the files in the root directory of your local server (e.g., `htdocs` in XAMPP).

3. Access the application through your web browser by visiting `http://localhost/your_project`.

That's it! You should now have the application running locally in your development environment.

