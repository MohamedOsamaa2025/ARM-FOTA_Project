<?php
// Define the file paths
$hexFile = 'BL_With_OFFSET.hex';  // Changed from FOTA_PROJECT3.hex
$recordFile = 'Record.txt';
$lineIndexFile = 'line_index.txt';

// Number of records to process at a time
$recordsToProcess = 28;  // Changed from 50 to 30

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

    // Calculate the ending index for this batch
    $endIndex = min($currentLineIndex + $recordsToProcess, count($hexContent));

    // Open the record file for writing (this will overwrite existing content)
    $recordHandle = fopen($recordFile, 'w');

    if ($recordHandle) {
        // Iterate through the lines to write 30 records
        for ($i = $currentLineIndex; $i < $endIndex; $i++) {
            // Parse the line if needed
            $parsedLine = parseHexLine($hexContent[$i]);

            // Write the parsed line to Record.txt
            fwrite($recordHandle, $parsedLine . PHP_EOL);
        }

        // Close the file handle
        fclose($recordHandle);

        // Update the line index file with the next line index
        file_put_contents($lineIndexFile, $endIndex);

        echo "Record.txt has been updated with the next $recordsToProcess records from the hex file.";

        // Check if all records have been processed
        if ($endIndex >= count($hexContent)) {
            // Delete the content of BL_With_OFFSET.hex
            file_put_contents($hexFile, '');

            // Delete the content of line_index.txt
            file_put_contents($lineIndexFile, '');

            echo " All records have been processed. The contents of BL_With_OFFSET.hex and line_index.txt have been deleted.";
        }
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
