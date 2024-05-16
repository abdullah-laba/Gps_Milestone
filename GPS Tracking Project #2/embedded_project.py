import serial
import plotly.express as px

latitudes = []
longitudes = []

def plot_trajectory():
    fig = px.scatter_mapbox(
                        lat=latitudes, 
                        lon=longitudes,
                        zoom= 18
                        )
    
    fig.update_layout(mapbox_style="open-street-map")
    fig.update_layout(margin={"r":0,"t":0,"l":0,"b":0})
    fig.show()


tiva_message = '-'

tiva = serial.Serial(
    port="COM4", baudrate=9600, bytesize=8, stopbits=serial.STOPBITS_ONE
)

while tiva_message:

    tiva_message = tiva.readline()
    if tiva_message:

        lat, long = map(float, str(tiva_message, 'ascii').split(','))
        latitudes.append(lat)
        longitudes.append(long)


plot_trajectory()
