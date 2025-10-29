class WeatherStation {
    constructor() {
        this.temperature = 20;
        this.pressure = 1013;
        this.observers = [];
    }

    subscribe(observer) {
        this.observers.push(observer);
        observer.update(this.getState());
        return () => this.unsubscribe(observer);
    }

    unsubscribe(observer) {
        const index = this.observers.indexOf(observer);
        if (index > -1) {
            this.observers.splice(index, 1);
        }
    }

    notify() {
        const state = this.getState();
        this.observers.forEach(observer => observer.update(state));
    }

    getState() {
        return {
            temperature: this.temperature,
            pressure: this.pressure
        };
    }

    setTemperature(temp) {
        this.temperature = temp;
        this.notify();
    }

    setPressure(pressure) {
        this.pressure = pressure;
        this.notify();
    }

    setBoth(temp, pressure) {
        this.temperature = temp;
        this.pressure = pressure;
        this.notify();
    }
}

class Display {
    constructor(id, weatherStation) {
        this.id = id;
        this.updateCount = 0;
        this.element = this.createDOM();
        this.unsubscribe = weatherStation.subscribe(this);
    }

    createDOM() {
        const display = document.createElement('div');
        display.className = 'display';
        display.id = `display-${this.id}`;
        display.innerHTML = `
            <h3>
                Display #${this.id}
                <button class="remove-btn" onclick="removeDisplay(${this.id})">Eliminar</button>
            </h3>
            <div class="display-data">
                <div class="data-item">
                    <div class="data-label">Temperatura</div>
                    <div class="data-value temp">--</div>
                </div>
                <div class="data-item">
                    <div class="data-label">Presión</div>
                    <div class="data-value pressure">--</div>
                </div>
            </div>
            <div class="update-count">Actualizaciones: <span class="count">0</span></div>
        `;
        document.getElementById('displays').appendChild(display);
        return display;
    }

    update(state) {
        this.updateCount++;
        const tempEl = this.element.querySelector('.temp');
        const pressureEl = this.element.querySelector('.pressure');
        const countEl = this.element.querySelector('.count');

        tempEl.textContent = `${state.temperature.toFixed(1)}°C`;
        pressureEl.textContent = `${state.pressure.toFixed(1)} hPa`;
        countEl.textContent = this.updateCount;

        // Animación de actualización
        this.element.style.background = '#e6fffa';
        setTimeout(() => {
            this.element.style.background = '#f7fafc';
        }, 300);
    }

    destroy() {
        this.unsubscribe();
        this.element.remove();
    }
}

// Inicialización
const weatherStation = new WeatherStation();
const displays = new Map();
let displayIdCounter = 1;

// Crear displays iniciales
addDisplay();
addDisplay();

// Funciones globales
function updateTemperature() {
    const temp = parseFloat(document.getElementById('tempInput').value);
    weatherStation.setTemperature(temp);
}

function updatePressure() {
    const pressure = parseFloat(document.getElementById('pressureInput').value);
    weatherStation.setPressure(pressure);
}

function updateBoth() {
    const temp = parseFloat(document.getElementById('tempInput').value);
    const pressure = parseFloat(document.getElementById('pressureInput').value);
    weatherStation.setBoth(temp, pressure);
}

function addDisplay() {
    const id = displayIdCounter++;
    const display = new Display(id, weatherStation);
    displays.set(id, display);
}

function removeDisplay(id) {
    const display = displays.get(id);
    if (display) {
        display.destroy();
        displays.delete(id);
    }
}

// Permitir actualización con Enter
document.getElementById('tempInput').addEventListener('keypress', (e) => {
    if (e.key === 'Enter') updateTemperature();
});

document.getElementById('pressureInput').addEventListener('keypress', (e) => {
    if (e.key === 'Enter') updatePressure();
});