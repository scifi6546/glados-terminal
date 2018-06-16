class token:
    type=""
    content=""
    def __init__(self,type,content):
        self.type=type
        self.content=content
    def __str__(self):
        return "TOKEN   type: " + self.type + "    content: " + str(self.content)