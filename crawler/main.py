from icrawler.builtin import BingImageCrawler

crawler = BingImageCrawler(
    storage={
        "root_dir": "images"
    }
)

crawler.crawl(
    keyword="anime girl",
    max_num=10
)