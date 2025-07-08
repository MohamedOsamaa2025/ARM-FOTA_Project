<?php
// Define the file paths
$hexFile = 'AppCode.hex';  // Changed from FOTA_PROJECT3.hex
$recordFile = 'Record.txt';
$lineIndexFile = 'line_index.txt';

// Check if the hex file exists
if (file_exists($hexFile)) {
    // Read the hex file content into an array, each line is an array element
    $hexContent = file($hexFile, FILE_IGNORE_NEW_LINES | FILE_SKIP_EMPTY_LINES);

    // Open the record file for writing (this will overwrite existing content)
    $recordHandle = fopen($recordFile, 'w');

    if ($recordHandle) {
        // Iterate through all lines in the hex file
        foreach ($hexContent as $line) {
            // Parse the line if needed
            $parsedLine = parseHexLine($line);

            // Write the parsed line to Record.txt
            fwrite($recordHandle, $parsedLine . PHP_EOL);
        }

        // Close the file handle
        fclose($recordHandle);

        // Delete the content of BL_With_OFFSET.hex after processing all records
        file_put_contents($hexFile, '');

        // Delete the content of line_index.txt
        file_put_contents($lineIndexFile, '');

        echo "Record.txt has been updated with all the records from the hex file.";
        echo " All records have been processed. The contents of BL_With_OFFSET.hex and line_index.txt have been deleted.";
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
