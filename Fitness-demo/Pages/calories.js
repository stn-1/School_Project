$(function () {
  $("#workout-form").on("submit", function (event) {
    event.preventDefault();

    const workout = $("#workout").val();
    const duration = $("#duration").val();
    let calo = 0;
    if (workout === "Walking") {
      calo = duration * 3.33;
    } else if (workout === "Running") {
      calo = duration * 16.66;
    } else {
      calo = duration * 10;
    }

    console.log(calo);
    $("#result").html(calo.toFixed(2) + " Calories");
  });
});
