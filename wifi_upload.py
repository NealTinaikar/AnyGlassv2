import io
import os
from http.server import BaseHTTPRequestHandler, HTTPServer
from google.cloud import speech_v1p1beta1 as speech

os.environ["GOOGLE_APPLICATION_CREDENTIALS"] = r"C:\Users\nealt\OneDrive\Documents\Arduino\AnyGlass_v2\testing\primordial-gate-418805-17a74804f114.json"

class CustomRequestHandler(BaseHTTPRequestHandler):
    def _set_headers(self, status_code):
        self.send_response(status_code)
        self.send_header('Content-type', 'text/plain')
        self.end_headers()

    def do_POST(self):
        content_length = int(self.headers['Content-Length'])
        data = self.rfile.read(content_length)

        if self.path == "/transcribe":
            with open("recording.wav", 'wb') as f:
                f.write(data)
            transcription = speech_to_text_api("recording.wav")
            self._set_headers(200)
            self.wfile.write(transcription.encode())
        else:
            self._set_headers(405)

def speech_to_text_api(file_name):
    client = speech.SpeechClient()

    with io.open(file_name, "rb") as audio_file:
        content = audio_file.read()

    audio = speech.RecognitionAudio(content=content)

    config = speech.RecognitionConfig(
        encoding=speech.RecognitionConfig.AudioEncoding.LINEAR16,
        sample_rate_hertz=16000,
        language_code="en-US",
    )

    response = client.recognize(config=config, audio=audio)

    transcription = ""
    for result in response.results:
        transcription += result.alternatives[0].transcript + "\n"

    print(f"Transcription: {transcription}")
    return transcription

server_address = ('', 5000)
httpd = HTTPServer(server_address, CustomRequestHandler)
print(f'Starting server at {server_address[0]}:{server_address[1]}')
httpd.serve_forever()


