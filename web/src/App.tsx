import { Button } from "@/components/ui/button"
import { QWebChannel } from 'qwebchannel';


function test() {
  if (window.qt) {
    new QWebChannel(window.qt.webChannelTransport, (channel) => {
      const backend = (channel).objects.backend;
      backend.callFromJs("哈罗 C++，我是前端精灵！");

      backend.sendToJs.connect((message: string) => {
        console.log("收到来自 C++ 的主动通知:", message);
      });
    });
  }
}

export default function App() {

  return (
    <div className="min-h-svh">
      <Button onClick={test}>Button</Button>
      <div className="font-mono text-xs text-muted-foreground">
        (Press <kbd>d</kbd> to toggle dark mode)
      </div>
    </div>
  )
}
