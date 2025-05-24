$(function () {
  // Handle the form submission
  $("#custom-form").on("submit", function (event) {
    event.preventDefault(); // Prevent the default form submission

    // Get form data
    const formData = $(this).serialize(); // Serializes the form data into a query string

    // Access individual form fields
    const weight = $("#weight").val();
    const height = $("#height").val();

    let valid = true; // Initialize the valid flag

    // Validate weight
    if (weight <= 0 || isNaN(weight)) {
      $("#WeightError").text("Please enter a valid weight.");
      valid = false;
    } else {
      $("#WeightError").text(""); // Clear the error message if valid
    }

    // Validate height
    if (height <= 0 || isNaN(height)) {
      $("#HeightError").text("Please enter a valid height.");
      valid = false;
    } else {
      $("#HeightError").text(""); // Clear the error message if valid
    }

    // Only perform the BMI calculation if inputs are valid
    if (valid) {
      const heightInMeters = parseFloat(height) / 100; // Convert height to meters
      const bmi = (
        parseFloat(weight) /
        (heightInMeters * heightInMeters)
      ).toFixed(2); // Calculate BMI
      let body = "";

      // Determine the BMI category

      if (bmi < 18.5) {
        body = "Underweight";
      } else if (bmi >= 18.5 && bmi <= 24.9) {
        body = "Normal";
      } else if (bmi >= 25 && bmi < 30) {
        body = "Overweight";
      } else {
        body = "Overweight";
      }

      // Display the results
      $(".result1").html(bmi);
      $(".result2").html("You have a " + body + " body mass.");
    }
  });
});
