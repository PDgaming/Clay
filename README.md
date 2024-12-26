# Document Viewer Application

This application is a simple document viewer built using the **Clay** UI layout library. It allows users to view a list of documents and read their contents in a clean and responsive interface. The application leverages the high-performance capabilities of the Clay library to render the UI efficiently.

## Features

- **Responsive Layout**: The application uses a flex-box-like layout model to adapt to different screen sizes.
- **Document Navigation**: Users can navigate through a list of documents and view their titles and contents.
- **Hover Effects**: The UI provides visual feedback when hovering over sidebar buttons.
- **Scrolling Support**: The main content area supports vertical scrolling for documents that exceed the visible area.

## Getting Started

### Prerequisites

- Ensure you have the following installed:
  - [C Compiler](https://gcc.gnu.org/) (e.g., GCC or Clang)
  - [Raylib](https://www.raylib.com/) for rendering graphics
  - [Clay Library](https://github.com/nicbarker/clay) for UI layout

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/PDgaming/First-Clay-Project
   cd [First-Clay-Project]
   ```

2. Download the Clay library:
   - Visit the [Clay GitHub repository](https://github.com/nicbarker/clay) and download the `clay.h` file.
   - Place `clay.h` in the same directory as your source files.

3. Install Raylib:
   - Follow the installation instructions on the [Raylib website](https://www.raylib.com/).

### Running the Application

1. Compile the application:
   ```bash
   gcc main.c -o DocumentViewer.exe -lraylib -lgdi32 -lwinmm
   ```

2. Run the application:
   ```bash
   ./DocumentViewer.exe
   ```
OR(if you are using Windows)
Just double click on the exe file in the repository to run the application.

### Usage

- Upon launching the application, you will see a sidebar with a list of documents.
- Click on a document title to view its contents in the main area.
- Use the scroll feature to navigate through longer documents.

## Contributing

If you would like to contribute to this project, please fork the repository and submit a pull request. Any improvements or bug fixes are welcome!

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Acknowledgments

- This application uses the **Clay** UI layout library created by [Nic Barker](https://github.com/nicbarker/clay).
- Special thanks to the Raylib community for their support and resources.
