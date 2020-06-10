from flask import Flask
app = Flask(__name__)

color = "null"

@app.route('/')
def index():
    global color
    return 'json{"color":"%s"}' % color


@app.route('/color/<colorInput>')
def changecolor(colorInput):
    global color
    color = colorInput


    return 'color change to %s' % color

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)

