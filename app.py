from flask import Flask, render_template
import requests

app = Flask(__name__)
esp32_ip = "http://192.168.1.36"
ESP32_PORT = "80"

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/forward')
def forward():
    requests.get(f"{esp32_ip}:{ESP32_PORT}/forward")
    return "Car moving forward"

@app.route('/reverse')
def reverse():
    requests.get(f"{esp32_ip}:{ESP32_PORT}/reverse")
    return "Car moving reverse"

@app.route('/left')
def left():
    requests.get(f"{esp32_ip}:{ESP32_PORT}/left")
    return "Car turning left"

@app.route('/right')
def right():
    requests.get(f"{esp32_ip}:{ESP32_PORT}/right")
    return "Car turning right"

@app.route('/stop')
def stop():
    requests.get(f"{esp32_ip}:{ESP32_PORT}/stop")
    return "Car stopped"

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)

