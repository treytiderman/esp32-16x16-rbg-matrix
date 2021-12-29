// Trey 12/09/21

// From Arduino
#include <Arduino.h>

// Web page
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">

<!-- Head -->
<head>

  <!-- Basic Page Needs -->
  <meta charset="utf-8">
  <title>Grid Paint</title>
  <meta name="description" content="">
  <meta name="author" content="">

  <!-- Metas -->
  <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1">

</head>

<!-- CSS -->
<style>

/* Reset */
*, *::before, *::after {
  box-sizing: border-box;
  padding: 0;
  margin: 0;
  line-height: inherit;
  color: inherit;
  font: inherit;
}

/* Base / Structure */
html {
  line-height: 2;
  font-size: 62.5%;
}
body {
  /* Body */
  margin: .5em;
  background: #111;
  /* Font */
  color: #ddd;
  font-size: 1.6rem;
  font-family: monospace;
}
main {
  margin: auto; /* Center on screen */
  width: 80vh; /* Width as % of height */
  width: 700px; /* Fixed width */
  max-width: 100%; /* Max width less than screen */
}
section {
  /* Don't overflow the section */
  max-width: 100%;
  overflow-x: auto;
  /* Look */
  margin-bottom: 1rem;
  padding: 0.5rem;
  background-color: #222;
  border-radius: .5rem;
  border: 2px solid #000;
  box-shadow: 0px 0px .5em 0px #000;
}

/* Grid */
ul {
  display: grid;
  grid-template-columns: repeat(16, minmax(5px, 1fr));
}
li,
.li {
  text-align: center;
  list-style: none;
  margin: 1px;
  background-color: #000;
  border-radius: .5rem;
  border: 1px solid #00000099;
  aspect-ratio: 1/1;
}
li:nth-child(120) {border-radius: .5rem .5rem  0rem .5rem;}
li:nth-child(121) {border-radius: .5rem .5rem .5rem  0rem;}
li:nth-child(136) {border-radius: .5rem  0rem .5rem .5rem;}
li:nth-child(137) {border-radius:  0rem .5rem .5rem .5rem;}
.li input[type="color"] {
  position: absolute;
  opacity: 0;
  height: 0;
  width: 0;
}

/* Inputs */
input,
button {
  cursor: pointer;
  background-color: #444;
  border: 2px solid #00000099;
  border-radius: .5rem;
  padding: 0 .5em 0 .5em;
}
input:focus,
button:active {
  background-color: #333;
}
input:focus,
button:focus {
  outline: 1px solid #ddd;
}
input:hover,
button:hover {
  opacity: 90%;
}

/* Flex utilities */
.flex {
  display: flex;
}
.grow {
  flex: 1 0 0%;
}

/* Cursor */
#clear,
#palette,
#pickerLabel {
  cursor: pointer;
}
#matrix {
  cursor: crosshair;
}


</style>
</head>
<body>

<!-- HTML -->
<main>

  <!-- Palette -->
  <section class="flex">

    <div class="grow" id="test">
      <button id="save">💾 Save</button>
      <button id="load">🔽 Load</button>
    </div>


    <div>
      <label for="brightness">🔆
        <input type="number" name="brightness" id="brightness" min="0" max="255" placeholder="20">
      </label>
    </div>

  </section>
  <section>

    <div>
      <ul id="palette">
        <label class="li" for="picker" id="pickerLabel" style="background-color: #00FFFF;">
          <input type="color" id="picker"></input>
        </label>
        <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li>
      </ul>
    </div>

  </section>

  <!-- Board -->
  <section oncontextmenu="return false;">
    <ul id="matrix">
      <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li>
      <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li>
      <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li>
      <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li>
      <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li>
      <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li>
      <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li>
      <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li>
      <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li>
      <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li>
      <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li>
      <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li>
      <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li>
      <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li>
      <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li>
      <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li> <li></li>
    </ul>
  </section>

  <!-- Shortcuts -->
  <aside style="color: #FFFFFF33; font-size: 1.2rem;">
    <p id="clear">» Click here or use the Delete key to clear</p>
    <p>» Right click and drag to erase</p>
    <p>» Middle click to copy color</p>
  </aside>

</main>

<!-- Javascript -->
<script defer>

// Global variables
const colorPalette = [
  '#000000', '#333333', '#8C8C8C', '#CCCCCC', '#FFFFFF',
  '#FF0000', '#FF9900', '#FFFF00', '#99FF00', '#00FF00',
  '#00FFFF', '#0099FF', '#0000FF', '#9900FF', '#FF00FF'
];
let drawColor = '#00FFFF'

// Palette
const picker = document.getElementById('picker');
const pickerLabel = document.getElementById('pickerLabel');
picker.addEventListener('input', () => {
  pickerLabel.style.backgroundColor = event.target.value;
  drawColor = event.target.value;
})
const palette = document.getElementById('palette');
const colors = palette.getElementsByTagName('li');
// Set palette colors
for (let i = 0; i < colors.length; i++) {
  colors[i].style.backgroundColor = colorPalette[i];
  colors[i].addEventListener('click', setDrawColor);
  function setDrawColor(event) {
    event.preventDefault();
    drawColor = window.getComputedStyle(event.target).getPropertyValue('background-color');
    console.log(drawColor);
  }
}

// Matrix
let drawing = false;
let erasing = false;
const matrix = document.getElementById('matrix');
const pixels = matrix.getElementsByTagName('li');
for (let i = 0; i < pixels.length; i++) {
  pixels[i].id = "pixel";

  // Event Listeners
  pixels[i].addEventListener('mousedown', drawStart);
  pixels[i].addEventListener('mousemove', drawMove);
  pixels[i].addEventListener('mouseup', drawStop);
  matrix.addEventListener('mouseleave', drawStop);
  pixels[i].addEventListener('touchmove', drawTouch);

  // Draw functions
  function drawStart(event) {
    event.preventDefault();
    // if left click then draw
    if (event.button == 0) {
      drawing = true;
      event.target.style.backgroundColor = drawColor;
    }
    // if middle click then copy color
    else if (event.button == 1) {
      drawColor = window.getComputedStyle(event.target).getPropertyValue('background-color');
    }
    // if right click then black
    else if (event.button == 2) {
      erasing = true;
      event.target.style.backgroundColor = "#000000";
    }
  }
  function drawMove(event) {
    event.preventDefault();
    if (drawing) {
      event.target.style.backgroundColor = drawColor;
    }
    else if (erasing) {
      event.target.style.backgroundColor = "#000000";
    }
  }
  function drawStop(event) {
    event.preventDefault();
    drawing = false;
    erasing = false;
  }
  function drawTouch(event) {
    event.preventDefault();
    var touch = event.touches[0];
    element = document.elementFromPoint(touch.pageX,touch.pageY);
    if (element.id == "pixel") {
      element.style.backgroundColor = drawColor;
    }
  }

}

// Clear matrix with the Delete key
document.addEventListener('keyup', () => {
  if (event.code == "Delete") {
    clearMatrix();
  }
})
const clear = document.getElementById('clear');
clear.addEventListener('click', clearMatrix)
function clearMatrix() {
  for (let i = 0; i < pixels.length; i++) {
    pixels[i].style.backgroundColor = '#000000';
  }
}

// Save
const save = document.getElementById('save');
save.addEventListener('click', sendColors);

// Load
const load = document.getElementById('load');
load.addEventListener('click', loadColors);
function loadColors(event) {
  getColors('matrix');
}

// Brightness
const brightness = document.getElementById('brightness');
brightness.addEventListener('blur', sendBrightness); // 'blur' is leaving focus

// On Load
window.addEventListener('load', onLoad);
function onLoad() {
  getColors('matrix');
  getBrightness('brightness');
}

// Get Text Content of ID - /api/v0/getBrightness?id
function getBrightness(id) {

  // Create and Send Request
  var xhr = new XMLHttpRequest(); // Request object
  xhr.open("GET", "/api/v0/getBrightness?" + id, true);
  console.log("Request:\t/api/v0/getBrightness?" + id);
  xhr.send();

  // Wait for response
  xhr.addEventListener("readystatechange", function () {
    if (this.readyState == 4 && this.status == 200) {
      console.log("Response:\t" + this.responseText);
      document.getElementById(id).value = this.responseText;
    }
  });

}

// Send Value of ID - /api/v0/sendBrightness?id=value
function sendBrightness(event) {

  // Create and Send Request
  var xhr = new XMLHttpRequest(); // Request object
  var id = event.target.id;
  var value = document.getElementById(id).value;
  xhr.open("GET", "/api/v0/sendBrightness?" + id + "=" + value, true);
  console.log("Request:\t/api/v0/sendBrightness?" + id + "=" + value);
  xhr.send();

  // Wait for response
  xhr.addEventListener("readystatechange", function() {
    if (this.readyState == 4 && this.status == 200) {
      console.log("Response:\t" + this.responseText);
    }
  });

}

// Get Text Content of ID - /api/v0/getTextContent?id
function getColors(id) {
  
  // Grid
  const grid = document.getElementById(id);
  const pixel = grid.getElementsByTagName('li');

  // Create and Send Request
  var xhr = new XMLHttpRequest(); // Request object
  xhr.open("GET", "/api/v0/getColors?" + id, true);
  console.log("Request:\t/api/v0/getColors?" + id);
  xhr.send();

  // Wait for response
  xhr.addEventListener("readystatechange", function () {
    if (this.readyState == 4 && this.status == 200) {
      // Convert to JSON
      let json = JSON.parse(this.responseText);
      console.log("Response:\n", json);

      // Set Backgroud Colors to Response
      json.colors.forEach( (color,i) => {
        pixel[i].style.backgroundColor = color;
      });
    }
  });

}

// Send Colors of the Grid - /api/v0/sendColors?pixel=color&pixel=color&pix...
function sendColors(event) {

  // Grid
  const grid = document.getElementById('matrix');
  const pixel = grid.getElementsByTagName('li');

  // Create and Send Request
  var xhr = new XMLHttpRequest(); // Request object
  var id = event.target.id;
  let colors = '';

  for (let i = 0; i < 256; i++) {
    let color = window.getComputedStyle(pixel[i]).getPropertyValue('background-color');
    colors += i + '=' + color;
    if (i != 255) {
      colors += '&';
    }
  }

  xhr.open("GET", "/api/v0/sendColors?" + colors, true);
  console.log("Request:\n/api/v0/sendColors?" + colors);
  xhr.send();

  // Wait for response
  xhr.addEventListener("readystatechange", function() {
    if (this.readyState == 4 && this.status == 200) {
      // Convert to JSON
      let json = JSON.parse(this.responseText);
      console.log("Response:\n", json);

      // Set Backgroud Colors to Response
      json.colors.forEach( (color,i) => {
        pixel[i].style.backgroundColor = color;
      });
    }
  });

}

</script>
</body>
</html>
)rawliteral";