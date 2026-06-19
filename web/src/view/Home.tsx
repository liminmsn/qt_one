import { Button } from "@/components/ui/button";
import { Field } from "@/components/ui/field";
import { Input } from "@/components/ui/input";
import GridView from "@/components/web/GridView";
import { Search, LoaderPinwheel } from "lucide-react";
import { QWebChannel } from "qwebchannel";
import { useState } from "react";

export interface Data {
    success: boolean;
    keyword: string;
    count: number;
    images: string[];
}

export default function () {
    const [query, setQuery] = useState("");
    const [data, setData] = useState<Data | undefined>(undefined);

    function search() {
        if (window.qt)
            new QWebChannel(window.qt.webChannelTransport, (channel) => {
                const backend = channel.objects.backend;
                backend.postMessage({ comm: 0, data: query });

                backend.sendMessage.connect((packet: { comm: number; data: any }) => {
                    console.log("收到来自 C++ 的数据包:", packet);
                    if (packet.comm == 100) {
                        setData(packet.data);
                    }
                    // // 根据不同的命令号（comm）分发业务
                    // switch (packet.comm) {
                    //     case 100: // 对应 C++ 发送的 100 成功指令
                    //         if (packet.data && packet.data.success) {
                    //             console.log("图片抓取成功！", packet.data.images);
                    //             // setImages(packet.data.images); // 更新瀑布流状态
                    //         }
                    //         break;
                    //     case 500: // 对应 C++ 投递的错误指令
                    //         alert("搜索失败: " + packet.data);
                    //         break;
                    //     default:
                    //         console.warn("收到未定义的前端命令号:", packet.comm);
                    // }
                });
            });
    }

    return (
        <div className="h-svh p-2">
            <div className="w-1/2 mx-auto mb-2 z-100 sticky top-2">
                <Field orientation="horizontal">
                    <Input className="backdrop-blur-sm bg-accent/10" type="search" placeholder="Search..." onChange={(e) => setQuery(e.target.value)} />
                    <Button onClick={search}><Search />Search</Button>
                </Field>
            </div>


            {data ? <GridView data={data} /> : <LoaderPinwheel className="anim" />}
        </div>
    );
}