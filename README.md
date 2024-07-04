# AskMe Project - README

## Project Overview

**AskMe** is a file-based C++ program designed to facilitate a question-and-answer system where users can ask questions and receive answers from others. The project is built to support multiple users simultaneously, ensuring that any updates made by one user are visible to others in real-time. The system retains previous states, allowing users to see past interactions each time they log in.

## Features

### User Authentication
- **Sign Up**: Users can create a new account by providing their name, email, username, and password.
- **Login/Logout**: Users can log in to access their account and log out when done.
- **Anonymous Questions**: Users can opt to allow or disallow anonymous questions.

### User Operations
- **Print Questions**: Users can print questions that are directed to them, from them, or view feed questions.
- **Ask Questions**: Users can post questions to others.
- **Answer Questions**: Users can respond to questions posed to them.
- **Delete Questions**: Users can delete their own questions or entire threads.
- **Support for Threads**: Users can answer questions within threads, with each original question acting as a parent for its respective thread.

### System Design
- **Unique IDs**: Each user and question is assigned a unique system-generated ID.
- **Thread Management**: Deleting a parent question will remove the entire thread.
- **Access Control**: Users can only view and edit their own questions. Actions such as removing a question asked to someone else are prohibited.

## Project Structure

### Files and Directories
- **main.cpp**: Contains the main program logic and user interface.
- **user.h/user.cpp**: Handles user-related functionalities including login, signup, and user operations.
- **question.h/question.cpp**: Manages question-related functionalities including asking, answering, and deleting questions.
- **system.h/system.cpp**: Manages the overall system state, including loading and saving data to files.

## Getting Started

### Prerequisites
- C++ Compiler (e.g., GCC, Clang)
- Standard C++ Library

## Usage

1. **Login or Sign Up**: Start by logging into an existing account or signing up for a new one.
2. **Ask Questions**: Use the interface to post new questions.
3. **Answer Questions**: View and respond to questions directed to you.
4. **Manage Questions**: Print, delete, or view questions and threads as needed.

## Future Enhancements

- **Parallel Session Demo**: A demonstration of parallel sessions will be added in the next update.
- **Enhanced Security**: Improvements to user authentication and data protection.
- **UI Enhancements**: Better user interface for easier navigation and use.

## Author

**Mostafa S. Ibrahim**
- Artificial Intelligence & Computer Vision Researcher
- PhD from Simon Fraser University - Canada
- Bachelor / MSc from Cairo University - Egypt
- Ex-Software Engineer / ICPC World Finalist
