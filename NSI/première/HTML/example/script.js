const elt = document.querySelector('#date')
const btn = document.querySelector('button.refresh')


btn.addEventListener('click', refreshDate)

function refreshDate() {
    elt.innerHTML = new Date()
}

refreshDate()
