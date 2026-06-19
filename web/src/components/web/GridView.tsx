import 'react-photo-view/dist/react-photo-view.css';
import { PhotoProvider, PhotoView } from 'react-photo-view';
import { Card } from "../ui/card"
import type { Data } from '@/view/Home';
import { useEffect } from 'react';

export default function ({ data }: { data?: Data }) {
    useEffect(() => { }, [data]);

    if (data) {
        return <PhotoProvider>
            <div className="columns-4 gap-2 space-y-2">
                {
                    data.images.map((url, idx) => {
                        return <div key={idx} className="break-inside-avoid">
                            <Card className="pb-0 cursor-pointer hover:opacity-90 transition-opacity">
                                <PhotoView src={url}>
                                    <img src={url} alt={`img-${idx}`} onError={(err) => {
                                        console.log(err, "图片加载错误！");
                                        const node = (err.target as HTMLImageElement).parentNode?.parentNode as any;
                                        node.remove();
                                    }} />
                                </PhotoView>
                            </Card>
                        </div>
                    })
                }
            </div>
        </PhotoProvider>
    }

    return <div>
        输入内容开始查询!
    </div>
}