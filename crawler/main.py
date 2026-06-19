from icrawler.builtin import BingImageCrawler
from icrawler.downloader import ImageDownloader
import sys
import json

result = []

class UrlDownloader(ImageDownloader):
    def download(self, task, default_ext, timeout=5, max_retry=3, **kwargs):
        global result
        result.append(task["file_url"])

def main():

    keyword = sys.argv[1] if len(sys.argv) > 1 else ""
    max_num = int(sys.argv[2]) if len(sys.argv) > 2 else 10

    # 这里的 storage 最好指定一个内存或临时位置，不过只获取 URL 的话这样也可以
    crawler = BingImageCrawler(
        downloader_cls=UrlDownloader,
    )

    crawler.crawl(
        keyword=keyword,
        max_num=max_num
    )

    # 💡 打印最终 JSON，加上 flush=True 让 C++ 端第一时间收到
    print(json.dumps({
        "success": True,
        "keyword": keyword,
        "count": min(len(result), max_num),
        "images": result[:max_num]
    }, ensure_ascii=False), flush=True)

if __name__ == "__main__":
    main()