<?php
if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    // Directory where the file will be saved
    $targetDirectory = __DIR__ . '/';
    
    // Define the target file name as BL_With_OFFSET.hex
    $targetFile = $targetDirectory . 'BL_With_OFFSET.hex';

    // Check if the file is a valid HEX file
    $fileType = strtolower(pathinfo($_FILES["hexFile"]["name"], PATHINFO_EXTENSION));
    if ($fileType != "hex") {
        echo "Sorry, only HEX files are allowed.";
        exit;
    }

    // Check if file upload is successful
    if (move_uploaded_file($_FILES["hexFile"]["tmp_name"], $targetFile)) {
        echo "<!DOCTYPE html>
        <html lang='en'>
        <head>
            <meta charset='UTF-8'>
            <meta name='viewport' content='width=device-width, initial-scale=1.0'>
            <title>Upload Complete</title>
            <style>
                body {
                    background-image: url('DONE.jpg'); /* Your new background image */
                    background-size: cover;
                    background-position: center;
                    background-repeat: no-repeat;
                    height: 100vh;
                    margin: 0;
                    display: flex;
                    justify-content: center;
                    align-items: center;
                    color: white;
                    font-family: Arial, sans-serif;
                    text-align: center;
                }
                h1 {
                    font-size: 2em;
                    margin-bottom: 20px;
                }
                a {
                    color: white;
                    text-decoration: underline;
                }
            </style>
        </head>
        <body>
            <div>
                <h1>Upload Complete!</h1>
                <p>The file has been uploaded successfully as BL_With_OFFSET.hex.</p>
            </div>
        </body>
        </html>";
    } else {
        echo "Sorry, there was an error uploading your file.";
    }
}
?>
