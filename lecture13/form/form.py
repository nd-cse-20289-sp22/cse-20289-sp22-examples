#!/usr/bin/env python3

import tornado.ioloop
import tornado.options
import tornado.web

# Constants

PORT = 9999

# Handlers

class FormHandler(tornado.web.RequestHandler):
    def get(self):
        # Get value for name argument from form submission
        name = self.get_argument('name', '')

        # Display greeting if Name is specified
        if name:
            self.write(f'<b>Hello, {name}</b>')

        # To get input from the user, we must create a form where each input
        # element has a name we can use to retrieve data.
        self.write(f'''
<h1>Enter Your Name:</h1>
<form>
    <input type="text" name="name" value="{name}">
    <input type="submit" value="Echo!">
</form>
''')

# Main Execution

def main():
    application = tornado.web.Application([
        (r'/', FormHandler),
    ])
    application.listen(PORT)

    tornado.options.parse_command_line()
    tornado.ioloop.IOLoop.current().start()

if __name__ == '__main__':
    main()
