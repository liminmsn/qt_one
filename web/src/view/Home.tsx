import { Button } from "@/components/ui/button";
import { Field } from "@/components/ui/field";
import { Input } from "@/components/ui/input";
import { Search } from "lucide-react";
import { QWebChannel } from "qwebchannel";
import { useState } from "react";

export default function Home() {
    const [query, setQuery] = useState("");

    function search() {
        if (window.qt) {
            new QWebChannel(window.qt.webChannelTransport, (channel) => {
                const backend = (channel).objects.backend;
                backend.callFromJs("哈罗 C++，我是前端精灵！");
                // backend.sendToJs.connect((message: string) => {
                //     console.log("收到来自 C++ 的主动通知:", message);
                // });
            });
        }
    }

    return <div className="p-6 pb-2 w-1/2 mx-auto">
        <Field orientation="horizontal">
            <Input type="search" placeholder="Search..." onChange={(e) => setQuery(e.target.value)} />
            <Button onClick={search}><Search />Search</Button>
        </Field>
    </div>
}