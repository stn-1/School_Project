// $(function(){
//     loadWorkouts();
//     $('#workout-form').on("submit",function(e) {
//         e.preventDefault();

//         const workout = $("#workout").val();
//         const duration = $("#duration").val();
//         var calo = 0;
//         if (workout ==="Walking"){
//             calo = duration*3.33;
//         } else if (workout ==="Running") {
//             calo = duration*16.66
//         } else {
//             calo = duration*10;
//         }
//         console.log(calo);

//         $.ajax({
//             url: "/workouts",
//             method: "POST",
//             contentType: "application/json",
//             data: JSON.stringify({ workout, duration }), // Convert data to JSON
//             success: function () {
//               // Reload the list of workouts after successfully adding a new one
//               loadWorkouts();
        
//               // Clear the input fields
//               $("#duration").val("");
//             },
//             error: function () {
//               alert("Failed to add workout. Please try again."); // Handle errors
//             },
//           });

//     })
// })

// function loadWorkouts() {
//     $.ajax({
//       url: "/workouts", // Server endpoint for getting workouts
//       method: "GET", // GET request to retrieve data
//       success: function (workouts) {
//         const $workoutList = $("#workout-list"); // Select the workout list element
//         $workoutList.empty(); // Clear the list before appending new data
  
//         // Loop through the array of workouts and add each one to the list
//         workouts.forEach(function (workout) {
//           $workoutList.append(
//             `<li>${workout.workout} - ${workout.duration} mins</li>`
//           );
//         });
//       },
//       error: function () {
//         alert("Failed to load workouts. Please try again."); // Handle errors
//       },
//     });
//   }


// // document.getElementById("workout-form").addEventListener("submit", async (e) => {
// //     e.preventDefault();
  
// //     const workout = document.getElementById("workout").value;
// //     const duration = document.getElementById("duration").value;
  
// //     const response = await fetch("/workouts", {
// //       method: "POST",
// //       headers: { "Content-Type": "application/json" },
// //       body: JSON.stringify({ workout, duration }),
// //     });
  
//     // if (response.ok) {
// //       loadWorkouts();
// //     }
// //   });
  
// //   async function loadWorkouts() {
// //     const response = await fetch("/workouts");
// //     const workouts = await response.json();
  
// //     const workoutList = document.getElementById("workout-list");
// //     workoutList.innerHTML = "";
  
// //     workouts.forEach(({ workout, duration }) => {
// //       const li = document.createElement("li");
// //       li.textContent = `${workout} - ${duration} mins`;
// //       workoutList.appendChild(li);
// //     });
// //   }
  
// //   loadWorkouts();
  