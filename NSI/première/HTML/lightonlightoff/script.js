const print = console.log
var counter = 0

function change() {
    counter++
    var img = document.getElementById("ampoule")
    var btn = document.getElementById("button")
    var body = document.getElementById("body")

    if (img.src.endsWith("lightOFF.png")) {
        img.src = "images/lightON.png"
        btn.innerHTML = "Éteindre"

        body.classList.toggle("on")
        btn.classList.toggle("on")
    } else if (img.src.endsWith("lightON.png")) {
        body.classList.toggle("on")
        btn.classList.toggle("on")

        if (counter > 20 && Math.random() < 0.05) {
            img.src = "images/lightBROKEN.png"
            btn.innerHTML = "Grillé…"
            btn.classList.toggle("broken")
        } else {
            img.src = "images/lightOFF.png"
            btn.innerHTML = "Allumer"
        }
    }
}
