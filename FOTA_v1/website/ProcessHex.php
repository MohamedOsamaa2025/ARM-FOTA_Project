<?php
// Define the file paths
$hexFile = 'BL_With_OFFSET.hex';  // Changed from FOTA_PROJECT3.hex
$recordFile = 'Record.txt';
$lineIndexFile = 'line_index.txt';

// Check if the hex file exists
if (file_exists($hexFile)) {
    // Read the hex file content into an array, each line is an array element
    $hexContent = file($hexFile, FILE_IGNORE_NEW_LINES | FILE_SKIP_EMPTY_LINES);

    // Check if the line index file exists
    if (file_exists($lineIndexFile)) {
        // Read the current line index from the file
        $currentLineIndex = (int)file_get_contents($lineIndexFile);
    } else {
        // If the line index file does not exist, start from the first line
        $currentLineIndex = 0;
    }

    // Ensure the current line index is within the array bounds
    if ($currentLineIndex >= count($hexContent)) {
        $currentLineIndex = 0; // Reset index if it exceeds the number of lines
    }

    // Get the current line to write
    $lineToWrite = $hexContent[$currentLineIndex];

    // Open the record file for writing (this will overwrite existing content)
    $recordHandle = fopen($recordFile, 'w');

    if ($recordHandle) {
        // Parse the line if needed
        $parsedLine = parseHexLine($lineToWrite);

        // Write the parsed line to Record.txt
        fwrite($recordHandle, $parsedLine . PHP_EOL);

        // Close the file handle
        fclose($recordHandle);

        // Update the line index file with the next line index
        file_put_contents($lineIndexFile, $currentLineIndex + 1);

        echo "Record.txt has been updated with the parsed hex file content.";
    } else {
        echo "Unable to open Record.txt for writing.";
    }
} else {
    echo "BL_With_OFFSET.hex file not found.";  // Updated file name in the error message
}

// Function to parse a line from the hex file
function parseHexLine($line) {
    // Implement your parsing logic here
    // For now, return the line as it is
    return $line;
}
?>
